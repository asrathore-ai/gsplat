#include "Ops.h"

std::tuple<at::Tensor, at::Tensor, at::Tensor> intersect_tile(
    const at::Tensor means2d,                    // [..., C, N, 2] or [nnz, 2]
    const at::Tensor radii,                      // [..., C, N, 2] or [nnz, 2]
    const at::Tensor depths,                     // [..., C, N] or [nnz]
    const at::optional<at::Tensor> image_ids,    // [nnz]
    const at::optional<at::Tensor> gaussian_ids, // [nnz]
    const uint32_t I,
    const uint32_t tile_size,
    const uint32_t tile_width,
    const uint32_t tile_height,
    const bool sort,
    const bool segmented
) {
    throw py::value_error(std::string(__func__) + " is not implemented");
}