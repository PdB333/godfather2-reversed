// FUNC_NAME: checkTargetFOV
// Function at 0x007c6ee0
// Checks if a target point is within the field-of-view cone of an observer.
// param_2: Pointer to observer's state (contains facing direction at offsets +0x277c, +0x2780, +0x2784)
// Returns 1 if target is inside cone (dot product > global threshold), 0 otherwise.

#include <cstdint>

// Global threshold for dot product (cosine of half FOV angle)
extern float g_fovDotProductThreshold;

// Helper: returns pointer to entity's position data (x at +0x30, y at +0x34, z at +0x38)
void* getEntityPosition();  // FUN_00471610

int checkTargetFOV(void* unused, int observerState) {
    // Invalidate sentinel check: -0x2770 (usually means no observer available)
    if (observerState == -0x2770) {
        return 0;
    }

    // Retrieve positions of two entities (likely observer and target)
    float* pos1 = (float*)getEntityPosition();  // +0x30 = x, +0x34 = y, +0x38 = z
    float* pos2 = (float*)getEntityPosition();  // same layout

    // Observer's forward direction vector (stored at +0x277c, +0x2780, +0x2784)
    float* dir = (float*)(observerState + 0x277c);

    // Compute direction from pos2 to pos1
    float dx = pos1[0] - pos2[0];  // +0x30
    float dy = pos1[1] - pos2[1];  // +0x34
    float dz = pos1[2] - pos2[2];  // +0x38

    // Dot product of observer's facing direction with (pos1 - pos2)
    float dot = dir[0] * dx + dir[1] * dy + dir[2] * dz;

    // If dot product exceeds threshold, target is within cone
    if (g_fovDotProductThreshold < dot) {
        return 1;
    }
    return 0;
}