#include "Ops.h"

std::tuple<at::Tensor, at::Tensor> projection_ewa_simple_fwd(
    const at::Tensor means,  // [..., C, N, 3]
    const at::Tensor covars, // [..., C, N, 3, 3]
    const at::Tensor Ks,     // [..., C, 3, 3]
    const uint32_t width,
    const uint32_t height,
    const CameraModelType camera_model
) {

}