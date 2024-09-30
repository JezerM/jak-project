
#include "IGen.h"

#include <memory>

#include "goalc/emitter/IGenArm64.h"
#include "goalc/emitter/IGenX86.h"

// https://armconverter.com/?code=ret
// https://developer.arm.com/documentation/ddi0487/latest
// https://github.com/darlinghq/darling/discussions/1376

namespace emitter {

std::unique_ptr<IGen> IGen::make_igen() {
  std::unique_ptr<IGen> igen = NULL;
  switch (get_cpu_info().target_arch) {
    case cpu_arch_arm64:
      igen = std::unique_ptr<IGenArm64>(new IGenArm64());
      break;
    case cpu_arch_x86_64:
      igen = std::unique_ptr<IGenX86>(new IGenX86());
      break;
    default:
      return NULL;
  }
  return igen;
}

std::unique_ptr<IGen> gIGen;

}  // namespace emitter
