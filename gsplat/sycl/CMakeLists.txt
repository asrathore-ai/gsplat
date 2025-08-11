cmake_minimum_required(VERSION 3.23...4.0)  # Need min 3.23 on Windows

set(CMAKE_C_COMPILER icx)
set(CMAKE_CXX_COMPILER icx)

project(gsplat_sycl)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (NOT SYCL_AOT_TARGETS)
        set (SYCL_AOT_TARGETS "spir64" CACHE STRING "Comma separated list of SYCL targets for ahead of time compilation. See https://github.com/intel/llvm/blob/sycl/sycl/doc/UsersManual.md for a full list.")
endif()

find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

find_package(IntelSYCL REQUIRED)


execute_process(
  COMMAND "${Python_EXECUTABLE}" -c "import torch.utils; print(torch.utils.cmake_prefix_path)"
  OUTPUT_STRIP_TRAILING_WHITESPACE
  OUTPUT_VARIABLE Torch_DIR_From_Python 
  RESULT_VARIABLE _torch_path_result    
  ERROR_QUIET                           
)
if(NOT _torch_path_result EQUAL 0)
  message(WARNING "Failed to get Torch CMake path from Python. "
                  "Make sure PyTorch is installed in the Python environment: ${Python_EXECUTABLE}")
  set(Torch_DIR_From_Python "")
endif()

if(Torch_DIR_From_Python AND IS_DIRECTORY "${Torch_DIR_From_Python}")
  set(Torch_DIR ${Torch_DIR_From_Python})
  message(STATUS "Found Torch CMake directory via Python: ${Torch_DIR}")
  find_package(Torch REQUIRED HINTS ${Torch_DIR_From_Python})
else()
  message(FATAL_ERROR "Could not find Torch via Python introspection. "
                      "Please ensure PyTorch is installed or set CMAKE_PREFIX_PATH/Torch_DIR manually.")
endif()


pybind_add_module(gsplat_sycl_kernels MODULE
    
    ${CMAKE_CURRENT_SOURCE_DIR}/ext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/adam.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/intersect_offset.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/intersect_tile.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_2dgs_fused_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_2dgs_fused_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_2dgs_packed_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_2dgs_packed_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ewa_3dgs_fused_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ewa_3dgs_fused_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ewa_3dgs_packed_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ewa_3dgs_packed_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ewa_simple_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ewa_simple_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/projection_ut_3dgs_fused.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/quat_scale_to_covar_preci_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/quat_scale_to_covar_preci_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_indices_2dgs.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_indices_3dgs.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_pixels_2dgs_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_pixels_2dgs_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_pixels_3dgs_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_pixels_3dgs_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_pixels_from_world_3dgs_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/rasterize_to_pixels_from_world_3dgs_fwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/relocation.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/spherical_harmonics_bwd.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/spherical_harmonics_fwd.cpp

)

target_include_directories( gsplat_sycl_kernels SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/../cuda/csrc/third_party/glm 
)

target_compile_options(gsplat_sycl_kernels PRIVATE -fsycl)
target_link_options(gsplat_sycl_kernels PRIVATE -fsycl -fsycl-targets=${SYCL_AOT_TARGETS})
target_link_libraries(gsplat_sycl_kernels PRIVATE IntelSYCL::SYCL_CXX torch)
target_compile_features(gsplat_sycl_kernels PUBLIC cxx_std_17)
# Fix for icx: error: '-MP' is not supported with offloading enabled
if (WIN32 AND NOT UNIX)
    get_target_property(CURRENT_OPTIONS gsplat_sycl_kernels COMPILE_OPTIONS)
    string(REPLACE "/MP" "" MODIFIED_OPTIONS "${CURRENT_OPTIONS}")
    set_target_properties(gsplat_sycl_kernels PROPERTIES COMPILE_OPTIONS "${MODIFIED_OPTIONS}")
endif ()
if (UNIX AND NOT APPLE)
   # Find libtorch_xpu and libsycl at runtime in Python environment
   set_target_properties(gsplat_sycl_kernels PROPERTIES INSTALL_RPATH 
           "$ORIGIN/../../torch/lib/;$ORIGIN/../../../../")
endif()
install(TARGETS gsplat_sycl_kernels
    LIBRARY DESTINATION "gsplat_sycl/_kernels"
)