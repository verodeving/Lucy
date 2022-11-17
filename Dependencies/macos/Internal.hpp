#pragma once
#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define APP_PRIVATE_IMPLEMENTATION
#include <Dependencies/macos/MetalKit/MetalKit.hpp>

namespace NS
{
    class Screen : public Referencing<Screen>
    {
    public:
        [[nodiscard]] static inline Screen* mainScreen()
        {
            return Object::sendMessage<Screen*>(_APPKIT_PRIVATE_CLS(NSScreen), _APPKIT_PRIVATE_SEL(mainScreen));
        }

        [[nodiscard]] inline CGRect frame()
        {
            return Object::sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(frame));
        }

        [[nodiscard]] inline int maximumFramesPerSecond()
        {
            return Object::sendMessage<int>(this, _APPKIT_PRIVATE_SEL(maximumFramesPerSecond));
        }
    };
}

#endif