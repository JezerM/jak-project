#pragma once

#include <cstddef>
#include <string>

size_t get_peak_rss();
void setup_cpu_info();

enum CpuArch {
  cpu_arch_unknown = 0,
  cpu_arch_x86_64 = 1,
  cpu_arch_arm64 = 2,
};

struct CpuInfo {
  bool initialized = false;
  bool has_avx = false;
  bool has_avx2 = false;

  std::string brand;
  std::string model;
  enum CpuArch arch
#if defined __x86_64__
      = cpu_arch_x86;
#elif defined __aarch64__
      = cpu_arch_arm64;
#else
      = cpu_arch_unknown;
#endif

  enum CpuArch target_arch = arch;
};

CpuInfo& get_cpu_info();
