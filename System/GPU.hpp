#pragma once
#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1
#include <Lucy.hpp>
#include <Core/Types.hpp>

namespace Lucy::System::GPU
{
    [[nodiscard]] inline auto FreeVRAM() -> u64
    {
        return __device_->;
    }
}

#endif