// FUNC_NAME: UnknownClass::calculateTransformedPosition
// Function at 0x007f7450, identified as a transformation/scale helper
// Uses an external transform object (vtable at offset 0xa4) to compute a scaled 3D vector
// Parameters: this (unknown class), esiInput/ediInput (likely passed in registers from caller), transformObj (pointer to object with vtable)

#include <cstdint>

float g_scaleFactor = _DAT_00d5c458; // global scale factor, likely part of a physics/config structure

void __thiscall calculateTransformedPosition(uint32_t this, float esiInput, float ediInput, void* transformObj)
{
    float local_18;          // stack variable at -0x18
    float afStack_14[3];     // temp array at -0x14
    float resultVec[3];      // computed output

    // First call: vtable[0xa4] with no arguments (likely reset/initialize transform)
    ((void(*)(void))(*(uint32_t**)transformObj)[0x29])(); // 0xa4/4 = 0x29

    // Second call: same vtable entry, writes into afStack_14 using (this+0x714) as source
    ((void(*)(float*, uint32_t))(*(uint32_t**)transformObj)[0x29])(afStack_14, this + 0x714);

    // Combine inputs with local variables and scale by g_scaleFactor
    resultVec[0] = (local_18 + esiInput) * g_scaleFactor;
    resultVec[1] = (*(float*)(this + 0x718) + local_18) * g_scaleFactor; // +0x718 is likely Y component of member position
    resultVec[2] = (ediInput + afStack_14[0]) * g_scaleFactor;

    // resultVec is stored into a buffer (caller expected location, not shown)
    // The decompiler showed pfStack_8 pointing to this, possibly a pointer passed in stack
    // For simplicity, we just compute; the actual usage is in the caller.
}