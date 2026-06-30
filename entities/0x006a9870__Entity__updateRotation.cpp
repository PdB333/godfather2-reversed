// FUNC_NAME: Entity::updateRotation
// Address: 0x006a9870
// Role: Updates smooth rotation interpolation for an entity, applying angular interpolation when a flag is set, with angle wrapping handling.

#include <cstdint>

// Constants from global data (likely defined elsewhere)
extern float g_fSomeFloat;          // DAT_01205214 - maybe delta time or target angle?
extern float g_fEpsilon;            // DAT_00e44598 - small value for angle comparison (maybe 0.0?)
extern uint32_t g_uAngleMask;       // DAT_00e44680 - mask to ignore low bits for angle wrapping (e.g., 0x3FFFFFFF)

// External functions called:
// FUN_005e6750 - probably sets a rotation angle on a transform handle (param1 = handle, param2 = angle)
// FUN_005e6700 - similar for another axis?
extern void __fastcall setRotationAngleY(uint32_t handle, float angle);
extern void __fastcall setRotationAngleZ(uint32_t handle, float angle);

// FUN_006a9510 and FUN_006a96e0 are other update methods (possibly fallbacks)
extern bool __fastcall FUN_006a9510(int thisPtr);
extern bool __fastcall FUN_006a96e0(int thisPtr);

// __fastcall: ecx = this
bool __fastcall Entity::updateRotation(int thisPtr)
{
    float fTargetAngle = g_fSomeFloat;  // DAT_01205214

    // Offset +0xe8: flag indicating whether rotation interpolation is active
    if (*(char *)(thisPtr + 0xe8) != 0)
    {
        // +0xd0: stored target angle (maybe set externally)
        *(float *)(thisPtr + 0xd0) = fTargetAngle;

        // +0xdc: current target angle (or maybe a clamped target), compare to global float
        if (*(float *)(thisPtr + 0xdc) < fTargetAngle)
        {
            // +0xe9: another flag (maybe "snap to target" or "use alternative path")
            if (*(char *)(thisPtr + 0xe9) != 0)
            {
                return FUN_006a96e0();  // handles immediate snap or alternate interpolation
            }
            return FUN_006a9510();      // standard fallback
        }

        // Compute interpolation factor 't' based on difference between current and previous target
        float fDiff = *(float *)(thisPtr + 0xdc) - *(float *)(thisPtr + 0xc4); // +0xc4: previous target angle?
        float t;
        if (fDiff <= g_fEpsilon)
        {
            t = 0.0f;
        }
        else
        {
            t = (fTargetAngle - *(float *)(thisPtr + 0xc4)) / fDiff;
        }

        // Interpolate first angle (e.g., yaw) from +0xcc to +0xe4
        // +0xcc: start angle for interpolation
        // +0xe0: end angle for interpolation (maybe from animation curve)
        // +0x200: that's offset 200 decimal = 0xc8? Wait, decompiled says "*(float *)(param_1 + 200)" which is 0xC8 (200 decimal = 0xC8). But offsets are given in hex: 0xc8 is likely the start angle for second interpolation? Actually careful: The decompiled says:
        // fVar1 = (*(float *)(param_1 + 0xe0) - *(float *)(param_1 + 200)) * fVar2 + *(float *)(param_1 + 200);
        // So +200 decimal = 0xC8. That is another start angle. So we have two interpolation pairs.
        // Likely: first pair: start=0xc8, end=0xe0; second pair: start=0xcc, end=0xe4.
        // But the code uses fVar2 for both interpolations. So we need to reconstruct correctly.
        // Let's rewrite based on the decompiled logic:

        float fInterpYaw = (*(float *)(thisPtr + 0xe0) - *(float *)(thisPtr + 0xC8)) * t + *(float *)(thisPtr + 0xC8);
        float fAngleMaskFloat = *(float *)&g_uAngleMask; // reinterpret the mask as float? No, the mask is used as integer on the difference.
        // Actually the code does: (float)((uint)(fVar1 - *(float *)(param_1 + 0xd4)) & DAT_00e44680)
        // So it converts the float difference to uint (bitwise), ANDs with mask, then converts back to float (but still integer bits). This is odd but typical for angle wrapping: subtracting angles and then masking to get shortest arc.
        // g_uAngleMask likely is something like 0x3FFFFFFF to ignore sign bits? Or 0xFFFFFFFF to ignore nothing? Need to be careful.

        // +0xd4: previously applied first angle (yaw)
        float fPrevYaw = *(float *)(thisPtr + 0xd4);
        float fYawDiff = fInterpYaw - fPrevYaw;
        uint32_t uYawDiff = *(uint32_t*)&fYawDiff; // reinterpret bits
        uYawDiff &= g_uAngleMask;
        float fMaskedDiff = *(float*)&uYawDiff; // convert back
        if (g_fEpsilon < fMaskedDiff)
        {
            // +0x88: handle for transform component (first axis)
            setRotationAngleY(*(uint32_t*)(thisPtr + 0x88), fInterpYaw);
            // +0xa0: another handle (possibly for second axis? Or duplicate)
            setRotationAngleY(*(uint32_t*)(thisPtr + 0xa0), fInterpYaw);
            *(float *)(thisPtr + 0xd4) = fInterpYaw;
        }

        // Second interpolation (e.g., pitch)
        float fInterpPitch = (*(float *)(thisPtr + 0xe4) - *(float *)(thisPtr + 0xcc)) * t + *(float *)(thisPtr + 0xcc);
        float fPrevPitch = *(float *)(thisPtr + 0xd8);
        float fPitchDiff = fInterpPitch - fPrevPitch;
        uint32_t uPitchDiff = *(uint32_t*)&fPitchDiff;
        uPitchDiff &= g_uAngleMask;
        float fMaskedPitchDiff = *(float*)&uPitchDiff;
        if (g_fEpsilon < fMaskedPitchDiff)
        {
            // +0x88 and +0xa0 are used again, but with different set function (Z rotation)
            setRotationAngleZ(*(uint32_t*)(thisPtr + 0x88), fInterpPitch);
            setRotationAngleZ(*(uint32_t*)(thisPtr + 0xa0), fInterpPitch);
            *(float *)(thisPtr + 0xd8) = fInterpPitch;
        }
    }
    return true;
}