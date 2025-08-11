#include "Ops.h"

namespace gsplat::sycl {
    
std::tuple<at::Tensor, at::Tensor> quat_scale_to_covar_preci_fwd(
    const at::Tensor quats,  // [..., 4]
    const at::Tensor scales, // [..., 3]
    const bool compute_covar,
    const bool compute_preci,
    const bool triu
) {
    throw py::value_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl