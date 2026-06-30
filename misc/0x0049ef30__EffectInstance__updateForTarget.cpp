// FUNC_NAME: EffectInstance::updateForTarget
#include <cstdint>

// Function: 0x0049ef30
// Role: Updates and renders a visual effect for a given target if the effect is active.
// Offsets:
//   this+0x10 : pointer to effect transform (e.g., position/quaternion)
//   this+0xA0 : texture or effect identifier (int)
//   this+0xB0 : short (e.g., alpha, opacity, or type)
//   this+0xB2 : byte flags (bit 0 = active)
//   target+0xB4 : int (e.g., target state or data)

void EffectInstance::updateForTarget(void* target, int param1)
{
    // Check if this effect instance is active (bit 0 of flags at +0xB2)
    if ((*(uint8_t*)(this + 0xB2) & 1) != 0) {
        // Pre-update function (FUN_0049fd00)
        effectPreUpdate(target);

        // Render/draw function (FUN_0042cfa0)
        effectDraw(
            *(void**)(g_global + 4), // Singleton pointer or state (DAT_012233a8+4)
            target,
            *(int*)(this + 0xA0),    // Texture/effect ID
            (void*)(this + 0x10),    // Transform pointer
            param1,
            *(int16_t*)(this + 0xB0), // Alpha or type
            *(int*)(target + 0xB4)    // Target-specific data
        );
    }
}