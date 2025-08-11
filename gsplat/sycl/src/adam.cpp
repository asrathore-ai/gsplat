#include "Ops.h"

namespace gsplat::sycl {
    
void adam(
    at::Tensor &param,                    // [..., D]
    const at::Tensor &param_grad,         // [..., D]
    at::Tensor &exp_avg,                  // [..., D]
    at::Tensor &exp_avg_sq,               // [..., D]
    const at::optional<at::Tensor> valid, // [...]
    const float lr,
    const float b1,
    const float b2,
    const float eps
) {
    throw py::value_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl