#include "Ops.h"

namespace gsplat::sycl {
    
std::tuple<at::Tensor, at::Tensor> projection_ewa_simple_fwd(
    const at::Tensor means,  // [..., C, N, 3]
    const at::Tensor covars, // [..., C, N, 3, 3]
    const at::Tensor Ks,     // [..., C, 3, 3]
    const uint32_t width,
    const uint32_t height,
    const CameraModelType camera_model
) {
    throw std::runtime_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl