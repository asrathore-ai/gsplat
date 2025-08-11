#include "Ops.h"

std::tuple<at::Tensor, at::Tensor, at::Tensor, at::Tensor, at::Tensor>
rasterize_to_pixels_3dgs_bwd(
    // Gaussian parameters
    const at::Tensor means2d,                   // [..., N, 2] or [nnz, 2]
    const at::Tensor conics,                    // [..., N, 3] or [nnz, 3]
    const at::Tensor colors,                    // [..., N, 3] or [nnz, 3]
    const at::Tensor opacities,                 // [..., N] or [nnz]
    const at::optional<at::Tensor> backgrounds, // [..., 3]
    const at::optional<at::Tensor> masks,       // [..., tile_height, tile_width]
    // image size
    const uint32_t image_width,
    const uint32_t image_height,
    const uint32_t tile_size,
    // intersections
    const at::Tensor tile_offsets, // [..., tile_height, tile_width]
    const at::Tensor flatten_ids,  // [n_isects]
    // forward outputs
    const at::Tensor render_alphas, // [..., image_height, image_width, 1]
    const at::Tensor last_ids,      // [..., image_height, image_width]
    // gradients of outputs
    const at::Tensor v_render_colors, // [..., image_height, image_width, 3]
    const at::Tensor v_render_alphas, // [..., image_height, image_width, 1]
    // options
    bool absgrad
) {
    
}