#include "Ops.h"

namespace gsplat::sycl {
    
at::Tensor intersect_offset(
    const at::Tensor isect_ids, // [n_isects]
    const uint32_t I,
    const uint32_t tile_width,
    const uint32_t tile_height
) {
    throw std::runtime_error(std::string(__func__) + " is not implemented");
}

} // namespace gsplat::sycl