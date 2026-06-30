// FUNC_NAME: Animated::clearAnimationSlots

#include <cstdint>

// Forward declarations of callees (assuming global context)
extern void* g_entityContext;     // unknown context pointer (passed via EDI)
extern bool __fastcall isStateValid(uint32_t state);   // FUN_0064bb50
extern void __fastcall releaseAnimationSlot(void* context, void* slot); // FUN_006527e0

void __thiscall Animated::clearAnimationSlots(uint32_t param) {
    // Save and clear a state byte at offset 0xf4 (e.g., animation flag)
    char savedState = *(char*)(this + 0xf4);
    *(char*)(this + 0xf4) = 0;

    if (isStateValid(savedState)) {
        // Build composite state from param (upper bits) and internal state at +0xb8
        uint32_t composite = ((param >> 8) << 8) | (*(uint32_t*)(this + 0xb8) >> 2);
        composite &= 0xffffff01; // Clear LSB

        if (!isStateValid(composite)) {
            // Release four animation slots (offset 0xd4..0xe0, each 4 bytes)
            releaseAnimationSlot(g_entityContext, *(void**)(this + 0xe0));
            releaseAnimationSlot(g_entityContext, *(void**)(this + 0xdc));
            releaseAnimationSlot(g_entityContext, *(void**)(this + 0xd8));
            releaseAnimationSlot(g_entityContext, *(void**)(this + 0xd4));
        }
    }
}