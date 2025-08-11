#include "Ops.h"

at::Tensor intersect_offset(
    const at::Tensor isect_ids, // [n_isects]
    const uint32_t I,
    const uint32_t tile_width,
    const uint32_t tile_height
) {
    throw py::value_error(std::string(__func__) + " is not implemented");
}