#include "Ops.h"

std::tuple<at::Tensor, at::Tensor> quat_scale_to_covar_preci_fwd(
    const at::Tensor quats,  // [..., 4]
    const at::Tensor scales, // [..., 3]
    const bool compute_covar,
    const bool compute_preci,
    const bool triu
) {
    
}