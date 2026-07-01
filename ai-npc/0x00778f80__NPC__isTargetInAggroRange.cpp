// FUNC_NAME: NPC::isTargetInAggroRange
// Address: 0x00778f80
// Role: Checks if the NPC's current target is within aggro range (based on a global threshold).
// Uses the brain component's virtual function at vtable offset 0x1a8 (index 106) which returns a float (likely distance/desire weight).
// The field at this+0x88 points into a sub-structure inside the brain component (brainBase = ptr - 0x48).

#include <cstdint>

// Global threshold for aggro range – compared against the float returned by the brain component's virtual function.
extern float gAggroRangeThreshold; // 0x00d6835c

bool __fastcall NPC::isTargetInAggroRange(NPC* thisPtr) {
    // +0x88: pointer to a sub-member inside the brain component (at offset 0x48 from the brain component base)
    int* brainSubPtr = *(int**)(reinterpret_cast<char*>(thisPtr) + 0x88);

    // Check for null or sentinel value (0x48 = 72 decimal, indicating invalid component)
    if (brainSubPtr == nullptr || brainSubPtr == reinterpret_cast<int*>(0x48)) {
        return false;
    }

    // Compute the brain component base by subtracting 0x48 (the pointer points to offset 0x48 inside the component)
    int* brainComponent = reinterpret_cast<int*>(reinterpret_cast<char*>(brainSubPtr) - 0x48);

    // Call virtual function at vtable offset 0x1a8 (index = 0x1a8 / 4 = 106).
    // This function likely returns a float (e.g., distance to threat, desire weight).
    float result = (*(float(__thiscall**)(int*))(*(int*)*brainComponent + 0x1a8))(brainComponent);

    // Compare against the global threshold
    if (gAggroRangeThreshold < result) {
        return true;
    }
    return false;
}