// FUNC_NAME: Collision::SweepQuery::testSweep

#include <cmath>

// Global constants from data segment (values unknown)
static const float g_sweepRadiusSq = DAT_00e44598;
static const float g_epsilonSq = DAT_00e2cbe0;
static const float g_invSqrtFactor = DAT_00e2b1a4;  // typically 1.0f
static const float g_angleRatioThreshold = DAT_00e2e780;

// __thiscall: ECX = this
uint __fastcall SweepQuery::testSweep(void /* this */) {
    // Note: param_1 in decompiled code = this pointer

    // Offsets relative to SweepQuery object:
    // +0x14: pointer to collision target (e.g., triangle data)
    // +0x64: origin X (float)
    // +0x68: origin Y (float)
    // +0x6c: origin Z (float)
    // +0x70: target offset X (float)
    // +0x74: target offset Y (float)
    // +0x78: target offset Z (float)
    // +0xa8: dot product threshold (float)
    // +0xe4: flags (uint8, bit0 controls whether to add offset)

    float originX = *(float*)((char*)this + 0x64);
    float originY = *(float*)((char*)this + 0x68);
    float originZ = *(float*)((char*)this + 0x6c);

    float originDistSq = originX * originX + originY * originY + originZ * originZ;
    if (originDistSq <= g_sweepRadiusSq) {
        // Early out: return default (low byte from EAX, preserved)
        // In original, uVar3 = in_EAX & 0xffffff00; we assume zero.
        return 0;
    }

    // Compute target position (origin + offset if flag not set)
    float targetX, targetY, targetZ;
    uint8 flags = *(uint8*)((char*)this + 0xe4);
    if ((flags & 1) == 0) {
        float offsetX = *(float*)((char*)this + 0x70);
        float offsetY = *(float*)((char*)this + 0x74);
        float offsetZ = *(float*)((char*)this + 0x78);
        targetX = originX + offsetX;
        targetY = originY + offsetY;
        targetZ = originZ + offsetZ;
    } else {
        targetX = originX;
        targetY = originY;
        targetZ = originZ;
    }

    // Normalize target vector
    float targetDistSq = targetX * targetX + targetY * targetY + targetZ * targetZ;
    float targetLen = 0.0f;
    float invTargetLen = 0.0f;
    if (targetDistSq > g_epsilonSq) {
        targetLen = sqrtf(targetDistSq);
        invTargetLen = g_invSqrtFactor / targetLen;
    }

    // Collision target object (e.g., triangle hit info)
    void* hitObj = *(void**)((char*)this + 0x14);  // +0x14
    // Normal vector from hit object (offets +0x10, +0x14, +0x18)
    float normalX = *(float*)((char*)hitObj + 0x10);
    float normalY = *(float*)((char*)hitObj + 0x14);
    float normalZ = *(float*)((char*)hitObj + 0x18);

    float normalDistSq = normalX * normalX + normalY * normalY + normalZ * normalZ;
    float normalLen = 0.0f;
    float invNormalLen = 0.0f;
    if (normalDistSq > g_epsilonSq) {
        normalLen = sqrtf(normalDistSq);
        invNormalLen = g_invSqrtFactor / normalLen;
    }

    // Normalized normal
    float normX = invNormalLen * normalX;
    float normY = invNormalLen * normalY;
    float normZ = invNormalLen * normalZ;
    if (normalLen <= 0.0f) {
        normX = 0.0f;
        normY = 0.0f;
        normZ = 0.0f;
    }

    // Extract identifier from hit object pointer address (low bits)
    // Original: uVar4 = (uint3)((uint)(iVar2 + 0x10) >> 8); -> uses pointer value + offset 0x10 right-shifted by 8.
    uint hitId = (uint)((uintptr_t)hitObj + 0x10) >> 8;

    // Dot product of target direction and hit normal
    float dot = invTargetLen * (targetX * normX + targetY * normY + targetZ * normZ);

    float angleThreshold = *(float*)((char*)this + 0xa8);
    float lenRatio = normalLen / targetLen;

    if (dot >= angleThreshold && lenRatio >= g_angleRatioThreshold) {
        // Return identifier shifted left 8 bits
        return hitId << 8;
    } else {
        // Return identifier with LSB set (CONCAT31(uVar4, 1))
        return (hitId << 8) | 1;
    }
}