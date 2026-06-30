// FUNC_NAME: GameEntity::setScaledProperty
// Address: 0x0047b5f0
// Function: Stores a scaled integer value derived from a float at offset 0x88.
// This pattern appears often in EA EARS games for converting world units (e.g., meters)
// to internal engine units using a global scale factor.

#include <math.h>

// Global conversion factor (DAT_00e2e230) – likely meters to internal units.
extern float g_engineUnitsPerMeter;

void __thiscall GameEntity::setScaledProperty(float valueInMeters)
{
    // Round to nearest integer after scaling
    int scaledValue = (int)roundf(valueInMeters * g_engineUnitsPerMeter);
    
    // Store at offset 0x88 (e.g., some property like health, distance, or ammunition)
    *(int *)((uintptr_t)this + 0x88) = scaledValue;
}