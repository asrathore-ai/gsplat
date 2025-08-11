#include "Ops.h"

namespace gsplat::sycl {
    
std::tuple<at::Tensor, at::Tensor> relocation(
    at::Tensor opacities, // [N]
    at::Tensor scales,    // [N, 3]
    at::Tensor ratios,    // [N]
    at::Tensor binoms,    // [n_max, n_max]
    const int n_max
) {
    throw py::value_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl