#include "Ops.h"
#include "Common.h"
#include "kernels/ComputeShFwdKernel.hpp"

#include <c10/xpu/XPUStream.h>

namespace gsplat::sycl {
    
at::Tensor spherical_harmonics_fwd(
    const uint32_t degrees_to_use,
    const at::Tensor dirs,               // [..., 3]
    const at::Tensor coeffs,             // [..., K, 3]
    const at::optional<at::Tensor> masks // [...]
) {
    throw std::runtime_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl