// FUNC_NAME: UnknownClass::setRandomCooldown
// Function address: 0x0076c090
// Role: Generates a random cooldown timer value within a range defined by global multipliers and clamps it to a maximum value from a singleton manager.
// This function is likely part of an AI or behavior component that needs to schedule periodic actions with randomized timing.

#include <cstdlib>
#include <cmath>

// Global floats for cooldown multipliers (likely defined elsewhere)
extern float _DAT_00d66000;   // +0x00: Max cooldown multiplier
extern float _DAT_00d66004;   // +0x04: Min cooldown multiplier
extern float DAT_00e44590;    // +0x00: 1.0f / RAND_MAX (scale factor for rand)

// Forward declaration of the singleton accessor
int* __fastcall getManagerSingleton();  // FUN_00800a90

void __thiscall setRandomCooldown(int thisPtr)
{
    // Check if the cooldown timer at +0x80 has expired (<= 0)
    if (*(int*)(thisPtr + 0x80) < 1)
    {
        int* manager = getManagerSingleton();
        int baseValue; // from manager +0x32c (max possible cooldown base)
        if (manager == nullptr)
            baseValue = 0;
        else
            baseValue = *(int*)(manager + 0x32c);

        // Calculate max timer value using global multiplier
        int maxTimer = static_cast<int>(static_cast<float>(baseValue) * _DAT_00d66000);

        // Get random factor in [0,1]
        int randInt = rand();
        // Calculate the range between max and min timer (min = baseValue * minMultiplier)
        float range = static_cast<float>(maxTimer) - static_cast<float>(baseValue) * _DAT_00d66004;
        float scaledRand = static_cast<float>(randInt) * DAT_00e44590 * range;
        int randomOffset = static_cast<int>(scaledRand + 0.5f); // round to nearest int

        // Random timer value between min and max
        int newTimer = maxTimer - randomOffset;
        *(int*)(thisPtr + 0x80) = newTimer;

        // Now clamp to the cap from manager +0x328 (max allowed cooldown)
        int capValue;
        if (manager == nullptr)
            capValue = 0;
        else
            capValue = *(int*)(manager + 0x328);

        // If the new timer exceeds the cap, or the difference between cap and timer is less than maxTimer, use the cap.
        if (capValue < newTimer || (capValue - newTimer) < maxTimer)
        {
            *(int*)(thisPtr + 0x80) = capValue;
        }
    }
    // Timer already running, do nothing
}