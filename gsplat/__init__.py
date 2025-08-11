import os
import sys
import torch
import warnings

BACKEND: str = ""
_backend_wrapper = None

FORCE_BACKEND = os.getenv("GSPLAT_BACKEND", "").lower()

if FORCE_BACKEND == "cuda" or (FORCE_BACKEND == "" and torch.cuda.is_available()):
    try:
        from .cuda import _wrapper as _backend_wrapper
        BACKEND = "cuda"
        print("gsplat: CUDA backend successfully loaded.", file=sys.stderr)
    except ImportError:
        if FORCE_BACKEND == "cuda":
            print("gsplat: Error! GSPLAT_BACKEND=cuda was set but CUDA backend failed to load.", file=sys.stderr)
        pass

if not BACKEND and (FORCE_BACKEND == "sycl" or FORCE_BACKEND == ""):
    try:
        from .sycl import _wrapper as _backend_wrapper
        BACKEND = "sycl"
        print("gsplat: SYCL backend successfully loaded.", file=sys.stderr)
    except ImportError as e:
        if FORCE_BACKEND == "sycl":
            print(f"gsplat: Error! GSPLAT_BACKEND=sycl was set but SYCL backend failed to load: {e}", file=sys.stderr)
        pass

if not BACKEND:
    print(
        "gsplat: Warning! No high-performance backend (CUDA or SYCL) found.",
        file=sys.stderr,
    )

if _backend_wrapper is not None:
    for func_name in dir(_backend_wrapper):
        if not func_name.startswith("_"):
            globals()[func_name] = getattr(_backend_wrapper, func_name)


from .compression import PngCompression
from .exporter import export_splats
from .optimizers import SelectiveAdam
from .rendering import (
    rasterization,
    rasterization_2dgs,
    rasterization_2dgs_inria_wrapper,
    rasterization_inria_wrapper,
)
from .strategy import DefaultStrategy, MCMCStrategy, Strategy
from .version import __version__


__all__ = [
    "BACKEND"
    "PngCompression",
    "DefaultStrategy",
    "MCMCStrategy",
    "Strategy",
    "rasterization",
    "rasterization_2dgs",
    "rasterization_inria_wrapper",
    "spherical_harmonics",
    "isect_offset_encode",
    "isect_tiles",
    "proj",
    "fully_fused_projection",
    "quat_scale_to_covar_preci",
    "rasterize_to_pixels",
    "world_to_cam",
    "rasterize_to_indices_in_range",
    "fully_fused_projection_2dgs",
    "rasterize_to_pixels_2dgs",
    "rasterize_to_indices_in_range_2dgs",
    "rasterization_2dgs_inria_wrapper",
    "RollingShutterType",
    "fully_fused_projection_with_ut",
    "rasterize_to_pixels_eval3d",
    "export_splats",
    "__version__",
    "SelectiveAdam",
    # Note: accumulate and accumulate_2dgs are not typically part of the public API
]