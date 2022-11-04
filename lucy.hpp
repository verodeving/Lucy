#pragma once
#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1
#if defined(lucy_mac) or defined(lucy_ios)
#include <Metal/Metal.h>

id<MTLDevice> __device_;

id<MTLLibrary> __library_;

id<MTLComputeCommandEncoder> __compute_command_encoder_;

#endif
#endif