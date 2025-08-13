 
#include <c10/xpu/XPUStream.h>

#include "Ops.h"
#include "Common.h"

namespace  gsplat::xpu {
    
std::tuple<at::Tensor, at::Tensor> projection_ewa_simple_bwd(
    const at::Tensor means,  // [..., C, N, 3]
    const at::Tensor covars, // [..., C, N, 3, 3]
    const at::Tensor Ks,     // [..., C, 3, 3]
    const uint32_t width,
    const uint32_t height,
    const CameraModelType camera_model,
    const at::Tensor v_means2d, // [..., C, N, 2]
    const at::Tensor v_covars2d // [..., C, N, 2, 2]
) {
    throw std::runtime_error(std::string(__func__) + " is not implemented");
}

} // namespace  gsplat::xpu