#include "Ops.h"

namespace gsplat::sycl {

at::Tensor null(const at::Tensor input) {
    throw std::runtime_error(std::string(__func__) + " is not implemented");
}

} //namespace gsplat::sycl