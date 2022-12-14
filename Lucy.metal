#include <metal_stdlib>

kernel void render(metal::texture2d<half, metal::access::write> text[[texture(0)]], uint2 gid[[thread_position_in_grid]])
{
    text.write(half4(0, 0, 1, 1), gid);
}
