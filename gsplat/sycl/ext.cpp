#include <torch/extension.h>

#include "Ops.h"
#include "Cameras.h"

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {

    py::enum_<gsplat::sycl::CameraModelType>(m, "CameraModelType")
        .value("PINHOLE", gsplat::sycl::CameraModelType::PINHOLE)
        .value("ORTHO", gsplat::sycl::CameraModelType::ORTHO)
        .value("FISHEYE", gsplat::sycl::CameraModelType::FISHEYE)
        .value("FTHETA", gsplat::sycl::CameraModelType::FTHETA)
        .export_values();

    m.def("null", &gsplat::sycl::null);

    m.def(
        "quat_scale_to_covar_preci_fwd", &gsplat::sycl::quat_scale_to_covar_preci_fwd
    );
    m.def(
        "quat_scale_to_covar_preci_bwd", &gsplat::sycl::quat_scale_to_covar_preci_bwd
    );

    m.def("spherical_harmonics_fwd", &gsplat::sycl::spherical_harmonics_fwd);
    m.def("spherical_harmonics_bwd", &gsplat::sycl::spherical_harmonics_bwd);

    m.def("adam", &gsplat::sycl::adam);
    m.def("relocation", &gsplat::sycl::relocation);

    m.def("intersect_tile", &gsplat::sycl::intersect_tile);
    m.def("intersect_offset", &gsplat::sycl::intersect_offset);

    m.def("projection_ewa_simple_fwd", &gsplat::sycl::projection_ewa_simple_fwd);
    m.def("projection_ewa_simple_bwd", &gsplat::sycl::projection_ewa_simple_bwd);
    m.def(
        "projection_ewa_3dgs_fused_fwd", &gsplat::sycl::projection_ewa_3dgs_fused_fwd
    );
    m.def(
        "projection_ewa_3dgs_fused_bwd", &gsplat::sycl::projection_ewa_3dgs_fused_bwd
    );
    m.def(
        "projection_ewa_3dgs_packed_fwd",
        &gsplat::sycl::projection_ewa_3dgs_packed_fwd
    );
    m.def(
        "projection_ewa_3dgs_packed_bwd",
        &gsplat::sycl::projection_ewa_3dgs_packed_bwd
    );

    m.def(
        "rasterize_to_pixels_3dgs_fwd", &gsplat::sycl::rasterize_to_pixels_3dgs_fwd
    );
    m.def(
        "rasterize_to_pixels_3dgs_bwd", &gsplat::sycl::rasterize_to_pixels_3dgs_bwd
    );
    m.def("rasterize_to_indices_3dgs", &gsplat::sycl::rasterize_to_indices_3dgs);

    m.def("projection_2dgs_fused_fwd", &gsplat::sycl::projection_2dgs_fused_fwd);
    m.def("projection_2dgs_fused_bwd", &gsplat::sycl::projection_2dgs_fused_bwd);
    m.def("projection_2dgs_packed_fwd", &gsplat::sycl::projection_2dgs_packed_fwd);
    m.def("projection_2dgs_packed_bwd", &gsplat::sycl::projection_2dgs_packed_bwd);

    m.def(
        "rasterize_to_pixels_2dgs_fwd", &gsplat::sycl::rasterize_to_pixels_2dgs_fwd
    );
    m.def(
        "rasterize_to_pixels_2dgs_bwd", &gsplat::sycl::rasterize_to_pixels_2dgs_bwd
    );
    m.def("rasterize_to_indices_2dgs", &gsplat::sycl::rasterize_to_indices_2dgs);

    m.def("projection_ut_3dgs_fused", &gsplat::sycl::projection_ut_3dgs_fused);
    m.def("rasterize_to_pixels_from_world_3dgs_fwd", &gsplat::sycl::rasterize_to_pixels_from_world_3dgs_fwd);
    m.def("rasterize_to_pixels_from_world_3dgs_bwd", &gsplat::sycl::rasterize_to_pixels_from_world_3dgs_bwd);

    // Cameras from 3DGUT
    py::enum_<ShutterType>(m, "ShutterType")
        .value("ROLLING_TOP_TO_BOTTOM", ShutterType::ROLLING_TOP_TO_BOTTOM)
        .value("ROLLING_LEFT_TO_RIGHT", ShutterType::ROLLING_LEFT_TO_RIGHT)
        .value("ROLLING_BOTTOM_TO_TOP", ShutterType::ROLLING_BOTTOM_TO_TOP)
        .value("ROLLING_RIGHT_TO_LEFT", ShutterType::ROLLING_RIGHT_TO_LEFT)
        .value("GLOBAL", ShutterType::GLOBAL)
        .export_values();

    py::class_<UnscentedTransformParameters>(m, "UnscentedTransformParameters")
        .def(py::init<>())
        .def_readwrite("alpha", &UnscentedTransformParameters::alpha)
        .def_readwrite("beta", &UnscentedTransformParameters::beta)
        .def_readwrite("kappa", &UnscentedTransformParameters::kappa)
        .def_readwrite("in_image_margin_factor", &UnscentedTransformParameters::in_image_margin_factor)
        .def_readwrite("require_all_sigma_points_valid", &UnscentedTransformParameters::require_all_sigma_points_valid);

    // FTheta Camera support
    py::enum_<FThetaCameraDistortionParameters::PolynomialType>(m, "FThetaPolynomialType")
        .value("PIXELDIST_TO_ANGLE", FThetaCameraDistortionParameters::PolynomialType::PIXELDIST_TO_ANGLE)
        .value("ANGLE_TO_PIXELDIST", FThetaCameraDistortionParameters::PolynomialType::ANGLE_TO_PIXELDIST)
        .export_values();
    py::class_<FThetaCameraDistortionParameters>(m, "FThetaCameraDistortionParameters")
        .def(py::init<>())
        .def_readwrite("reference_poly", &FThetaCameraDistortionParameters::reference_poly)
        .def_readwrite("pixeldist_to_angle_poly", &FThetaCameraDistortionParameters::pixeldist_to_angle_poly)
        .def_readwrite("angle_to_pixeldist_poly", &FThetaCameraDistortionParameters::angle_to_pixeldist_poly)
        .def_readwrite("max_angle", &FThetaCameraDistortionParameters::max_angle)
        .def_readwrite("linear_cde", &FThetaCameraDistortionParameters::linear_cde);
}