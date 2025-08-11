#include "Ops.h"

std::tuple<at::Tensor, at::Tensor> quat_scale_to_covar_preci_bwd(
    const at::Tensor quats,  // [..., 4]
    const at::Tensor scales, // [..., 3]
    const bool triu,
    const at::optional<at::Tensor> v_covars, // [..., 3, 3] or [..., 6]
    const at::optional<at::Tensor> v_precis  // [..., 3, 3] or [..., 6]
) {
    
}