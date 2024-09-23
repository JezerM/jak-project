#include <cstring>

#include "common/goos/Reader.h"

#include "goalc/debugger/disassemble.h"
#include <capstone/capstone.h>

#include "fmt/color.h"
#include "fmt/core.h"

std::string disassemble_arm64(u8* data, int len, u64 base_addr) {
  std::string result;
  csh handle;
  cs_insn* insn;

  cs_mode mode = (cs_mode)(CS_MODE_ARM + CS_MODE_LITTLE_ENDIAN);
  if (cs_open(CS_ARCH_AARCH64, mode, &handle) != CS_ERR_OK)
    return "";

  int offset = 0;

  while (offset < len) {
    int count = cs_disasm(handle, data + offset, len - offset, base_addr, 1, &insn);
    if (count > 0) {
      result += fmt::format("[0x{:x}]", insn->address);
      result += fmt::format("\t{:s}", insn->mnemonic);
      result += fmt::format("\t\t{:s}", insn->op_str);

      offset += insn->size;
      base_addr += insn->size;
      cs_free(insn, 1);
    } else {
      result += fmt::format("[0x{:x}] INVALID (0x{:02x})\n", base_addr, data[offset]);
      base_addr++;
      offset++;
    }
  }
  cs_close(&handle);

  return result;
}
std::string disassemble_arm64(u8* data, int len, u64 base_addr, u64 highlight_addr) {
  std::string result;
  csh handle;
  cs_insn* insn;

  cs_mode mode = (cs_mode)(CS_MODE_ARM + CS_MODE_LITTLE_ENDIAN);
  if (cs_open(CS_ARCH_AARCH64, mode, &handle) != CS_ERR_OK)
    return "";

  int offset = 0;

  ASSERT(highlight_addr >= base_addr);
  int mark_offset = int(highlight_addr - base_addr);
  while (offset < len) {
    char prefix = (offset == mark_offset) ? '-' : ' ';

    int count = cs_disasm(handle, data + offset, len - offset, base_addr, 1, &insn);
    if (count > 0) {
      result += fmt::format("{:c} [0x{:x}]", prefix, insn->address);
      result += fmt::format("\t{:s}", insn->mnemonic);
      result += fmt::format("\t\t{:s}", insn->op_str);
      result += "\n";

      offset += insn->size;
      base_addr += insn->size;
      cs_free(insn, 1);
    } else {
      result += fmt::format("{:c} [0x{:x}] INVALID (0x{:02x})\n", prefix, base_addr, data[offset]);
      base_addr++;
      offset++;
    }
  }
  cs_close(&handle);

  return result;
}

// how many "forms" to look at ahead of / behind rip when stopping
static constexpr int FORM_DUMP_SIZE_REV = 4;
static constexpr int FORM_DUMP_SIZE_FWD = 4;
// how long the bytecode part of the disassembly is, IR comes after this
static constexpr int DISASM_LINE_LEN = 60;

std::string disassemble_arm64_function(
    u8* data,
    int len,
    const goos::Reader* reader,
    u64 base_addr,
    u64 highlight_addr,
    const std::vector<InstructionInfo>& instructions,
    const std::vector<std::shared_ptr<goos::HeapObject>>& code_sources,
    const std::vector<std::string>& ir_strings,
    bool* had_failure,
    bool print_whole_function,
    bool omit_ir) {
  std::string result;
  csh handle;
  cs_insn* insn;

  cs_mode mode = (cs_mode)(CS_MODE_ARM + CS_MODE_LITTLE_ENDIAN);
  if (cs_open(CS_ARCH_AARCH64, mode, &handle) != CS_ERR_OK)
    return "";
  cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

  int current_instruction_idx = -1;
  int current_ir_idx = -1;
  int current_src_idx = -1;
  int rip_src_idx = -1;

  std::string current_filename;
  int current_file_line = -1;
  int current_offset_in_line = -1;

  int offset = 0;

  std::vector<std::pair<int, std::string>> lines;

  ASSERT(highlight_addr >= base_addr);
  int mark_offset = int(highlight_addr - base_addr);
  while (offset < len) {
    char prefix = (offset == mark_offset) ? '-' : ' ';

    int count = cs_disasm(handle, data + offset, len - offset, base_addr, 1, &insn);
    if (count > 0) {
      bool warn_messed_up = false;
      bool print_ir = false;
      // we should have a next instruction.
      if (current_instruction_idx + 1 >= int(instructions.size())) {
        warn_messed_up = true;
        if (had_failure) {
          *had_failure = true;
        }
      } else {
        // we should line up with the next instruction
        if (instructions.at(current_instruction_idx + 1).offset == offset) {
          // perfect, everything is lined up!
          current_instruction_idx++;
          while (current_instruction_idx + 1 < int(instructions.size()) &&
                 instructions.at(current_instruction_idx + 1).offset == offset) {
            current_instruction_idx++;
          }
        } else {
          printf("offset mess up, at %d, expected %d\n", offset,
                 instructions.at(current_instruction_idx + 1).offset);
          warn_messed_up = true;
          if (had_failure) {
            *had_failure = true;
          }
        }
      }

      if (!omit_ir && current_instruction_idx >= 0 &&
          current_instruction_idx < int(instructions.size())) {
        const auto& debug_instr = instructions.at(current_instruction_idx);
        if (debug_instr.kind == InstructionInfo::Kind::IR && debug_instr.ir_idx != current_ir_idx) {
          current_ir_idx = debug_instr.ir_idx;
          print_ir = true;
        }
      }

      if (strcmp(insn->mnemonic, "udf") == 0) {
        offset += insn->size;
        base_addr += insn->size;
        cs_free(insn, 1);
        continue;
      }

      std::string line;
      size_t line_size_offset = 0;

      if (!omit_ir && current_ir_idx >= 0 && current_ir_idx < int(ir_strings.size())) {
        auto source = reader->db.try_get_short_info(code_sources.at(current_ir_idx));
        if (source) {
          if (source->filename != current_filename ||
              source->line_idx_to_display != current_file_line ||
              source->pos_in_line != current_offset_in_line) {
            current_filename = source->filename;
            current_file_line = source->line_idx_to_display;
            current_offset_in_line = source->pos_in_line;
            ++current_src_idx;
            line +=
                fmt::format(fmt::emphasis::bold, "\n{}:{}\n", current_filename, current_file_line);
            line += fmt::format(fg(fmt::color::orange), "-> {}\n", source->line_text);
            std::string pointer(current_offset_in_line + 3, ' ');
            pointer += "^\n";
            line += fmt::format(fmt::emphasis::bold | fg(fmt::color::lime_green), "{}", pointer);
            line_size_offset = line.size();
          }
        }
      }

      if (prefix != ' ') {
        line += fmt::format(fmt::emphasis::bold | fg(fmt::color::red), "{:c} [0x{:X}] ", prefix,
                            base_addr);
        rip_src_idx = current_src_idx;
      } else {
        line += fmt::format("{:c} [0x{:X}] ", prefix, base_addr);
      }

      line += fmt::format(" {:s}", insn->mnemonic);
      line += fmt::format(" {:s}", insn->op_str);

      if (print_ir && current_ir_idx >= 0 && current_ir_idx < int(ir_strings.size())) {
        if (line.size() - line_size_offset < DISASM_LINE_LEN) {
          line.append(DISASM_LINE_LEN - (line.size() - line_size_offset), ' ');
        }
        line += " ";
        line += ir_strings.at(current_ir_idx);
      }

      if (warn_messed_up) {
        line += " ;; function's instruction do not align with debug data, something is wrong.";
      }

      line += "\n";
      lines.push_back(std::make_pair(current_src_idx, line));

      offset += insn->size;
      base_addr += insn->size;
      cs_free(insn, 1);
    } else {
      lines.push_back(std::make_pair(
          current_src_idx,
          fmt::format("{:c} [0x{:x}] INVALID (0x{:02x})\n", prefix, base_addr, data[offset])));
      base_addr++;
      offset++;
    }
  }
  cs_close(&handle);

  for (auto& line : lines) {
    if (print_whole_function || (line.first >= rip_src_idx - FORM_DUMP_SIZE_REV &&
                                 line.first < rip_src_idx + FORM_DUMP_SIZE_FWD)) {
      result.append(line.second);
    }
  }

  return result;
}
