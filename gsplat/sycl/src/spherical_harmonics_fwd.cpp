#include "Ops.h"

at::Tensor spherical_harmonics_fwd(
    const uint32_t degrees_to_use,
    const at::Tensor dirs,               // [..., 3]
    const at::Tensor coeffs,             // [..., K, 3]
    const at::optional<at::Tensor> masks // [...]
) {
    
}