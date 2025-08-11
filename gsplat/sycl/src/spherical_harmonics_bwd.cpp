#include "Ops.h"

namespace gsplat::sycl {
    
std::tuple<at::Tensor, at::Tensor> spherical_harmonics_bwd(
    const uint32_t K,
    const uint32_t degrees_to_use,
    const at::Tensor dirs,                // [..., 3]
    const at::Tensor coeffs,              // [..., K, 3]
    const at::optional<at::Tensor> masks, // [...]
    const at::Tensor v_colors,            // [..., 3]
    bool compute_v_dirs
) {
    throw std::runtime_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl