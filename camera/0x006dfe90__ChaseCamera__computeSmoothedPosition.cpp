// FUNC_NAME: ChaseCamera::computeSmoothedPosition

#include <cstdint>

// Global constants (from data references)
extern float kLerpFactorA;   // _DAT_00d577a0
extern float kLerpFactorB;   // _DAT_00d5780c
extern float kCameraOffsetX; // DAT_00e44564 (world-space offset in X)

// Forward declarations of called functions
void transformPositionByTarget(float* outPos, int targetEntity); // FUN_007c6f70
int getGlobalManager(); // FUN_00471610

// This function computes a smoothed camera position based on target entity state.
// param_1: this (ChaseCamera instance)
// param_2: outPosition (output float[3])
// param_3: pTargetEntity (pointer to target entity, e.g. Player or Vehicle)
void __thiscall ChaseCamera::computeSmoothedPosition(int thisPtr, float* outPosition, int pTargetEntity)
{
    uint32_t flags = *(uint32_t*)(pTargetEntity + 0x8E0); // Entity flags
    bool bit26 = (flags >> 0x1A) & 1; // Check bit 26
    bool bit25 = (flags >> 0x19) & 1; // Check bit 25
    bool bit30 = (flags >> 0x1E) & 1; // Check bit 30 (used later)
    bool bit0  = flags & 1;           // Check bit 0

    if (bit26 == 0 && bit25 != 0) {
        // Branch for "chase" or "following" mode
        transformPositionByTarget(outPosition, pTargetEntity); // Applies target-relative offset
        outPosition[1] += *(float*)(thisPtr + 0x18C); // Add vertical offset (maybe bone or camera height)

        float* vOffset;
        if (pTargetEntity == -0x2770) { // Sentinel value for "no target" (likely #define ENTITY_NULL)
            int mgr = getGlobalManager();
            vOffset = (float*)(mgr + 0x20); // Global camera offset vector
        } else {
            vOffset = (float*)(pTargetEntity + 0x277C); // Entity-specific offset (e.g., vehicle seat)
        }

        float speedFactor;
        if (bit30 == 0) {
            speedFactor = *(float*)(thisPtr + 0x1A0); // Normal speed factor
        } else {
            speedFactor = *(float*)(thisPtr + 0x19C); // Alternate speed factor (e.g., when braking)
        }

        float newX = vOffset[2] * speedFactor + outPosition[0];
        float newY = kLerpFactorA * speedFactor + outPosition[1];
        float newZ = (kCameraOffsetX - vOffset[0]) * speedFactor + outPosition[2];

        outPosition[0] = newX;
        outPosition[1] = newY;
        outPosition[2] = newZ;

        float blendThreshold = *(float*)(thisPtr + 0xF4); // Blend time or distance threshold
        if (blendThreshold < kLerpFactorB) {
            float blendFactor = kLerpFactorB - blendThreshold;
            // Lerp toward desired target position (stored at this+0x118)
            outPosition[0] = (*(float*)(thisPtr + 0x118) - outPosition[0]) * blendFactor + outPosition[0];
            outPosition[1] = (*(float*)(thisPtr + 0x11C) - outPosition[1]) * blendFactor + outPosition[1];
            outPosition[2] = (*(float*)(thisPtr + 0x120) - outPosition[2]) * blendFactor + outPosition[2];
        }
        return;
    }

    if (bit0 == 0 && bit26 == 0) {
        // Branch for "free" or "looking around" mode
        int mgr = getGlobalManager();
        *(uint64_t*)outPosition = *(uint64_t*)(mgr + 0x30); // Copy 2 floats (X and Z?)
        outPosition[2] = *(float*)(mgr + 0x38); // Copy third float
        outPosition[1] += *(float*)(thisPtr + 0x158); // Add vertical offset

        float blendThreshold = *(float*)(thisPtr + 0xF4);
        if (kLerpFactorA < blendThreshold) {
            outPosition[0] = (*(float*)(thisPtr + 0x118) - outPosition[0]) * blendThreshold + outPosition[0];
            outPosition[1] = (*(float*)(thisPtr + 0x11C) - outPosition[1]) * blendThreshold + outPosition[1];
            outPosition[2] = (*(float*)(thisPtr + 0x120) - outPosition[2]) * blendThreshold + outPosition[2];
        }
        return;
    }

    // Fallback: use the stored target position directly
    *(uint64_t*)outPosition = *(uint64_t*)(thisPtr + 0x118);
    outPosition[2] = *(float*)(thisPtr + 0x120);
    return;
}