#include "Ops.h"

std::tuple<at::Tensor, at::Tensor> relocation(
    at::Tensor opacities, // [N]
    at::Tensor scales,    // [N, 3]
    at::Tensor ratios,    // [N]
    at::Tensor binoms,    // [n_max, n_max]
    const int n_max
) {
    
}