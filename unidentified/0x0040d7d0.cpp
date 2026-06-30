// 0x0040d7d0
// Thin accessor for the shared menu/UI context handle used by nearby menu code.
//
// The function is a direct global getter in the original binary. Call sites
// cache this 32-bit value into screen state and compare it against the previous
// value when transitioning menu modes. The exact engine object behind the
// handle is still inferred from usage, so the naming stays conservative.

#include <cstdint>

extern "C" {
    // Shared 32-bit menu/UI context value returned by the accessor below.
    // Ghidra labeled this DAT_0120524c.
    extern std::uint32_t g_MenuContextHandle;
}

extern "C" std::uint32_t GetMenuContextHandle()
{
    return g_MenuContextHandle;
}
