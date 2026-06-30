// FUNC_NAME: CombatKnowledge::selectTargetBetweenTwo
// Address: 0x006fd480
// Identifies and selects between two potential targets (stored at this+0x180 and this+0x1b8) based on a threshold probability and random values.
// If conditions are met, sets the output target address to one of the two target fields and an index (0 or 1).

#include <cstddef>

void __thiscall CombatKnowledge::selectTargetBetweenTwo(int thisPtr, int* outTargetAddress, int* outChoice, float threshold)
{
    float random1;
    float random2;

    if (outTargetAddress == nullptr) {
        return;
    }

    // Two independent random values in [0,1)
    random1 = getRandomFloat();
    random2 = getRandomFloat();

    if (random1 <= random2) {
        // If random1 is less than random2 and threshold is small enough,
        // pick the target at this+0x1b8.
        if ((random1 < random2) && (threshold < random2) && (threshold < (random2 - random1))) {
            *outTargetAddress = thisPtr + 0x1b8; // Second target (e.g., optional cover/combatant)
            *outChoice = 1;
        }
    } else {
        // If random2 is smaller than random1 and threshold is small enough,
        // pick the target at this+0x180.
        if ((threshold < random1) && (threshold < (random1 - random2))) {
            *outTargetAddress = thisPtr + 0x180; // First target (e.g., primary cover/combatant)
            *outChoice = 0;
            return;
        }
    }
    // If neither branch fired, the output pointers remain unchanged (caller should handle default).
}