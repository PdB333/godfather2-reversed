// FUNC_NAME: ControllerManager::processActionTriggers
// Function at 0x008a4100: Checks six buffered action values against a threshold and triggers actions if exceeded; then clears the buffer.

#include <cstdint>

// Forward declarations of helper functions
void addPlayerAction(uint32_t actionId, uint32_t rawValue);     // calls FUN_00907a50 (indices 0,27,28)
void addPlayerActionAlt(uint32_t actionId, uint32_t rawValue);  // calls FUN_00907ac0 (indices 29,30,32)

// Global data (defined elsewhere)
extern float gAnalogTriggerThreshold; // DAT_00e44598 - minimum threshold for analog triggers
extern uint32_t gActionMask;          // DAT_00e44680 - mask applied to action values
extern uint32_t gActionValues[6];     // base at 0x0112eb94, offsets: 0x94,0x98,0x9c,0xa0,0xa4,0xa8

void processActionTriggers()
{
    // Check first action (index 0) - e.g., primary attack
    if (gAnalogTriggerThreshold < static_cast<float>(gActionValues[0] & gActionMask))
    {
        addPlayerAction(0, gActionValues[0]);
    }

    // Check second action (index 1) - e.g., weapon action 1
    if (gAnalogTriggerThreshold < static_cast<float>(gActionValues[1] & gActionMask))
    {
        addPlayerAction(27, gActionValues[1]);
    }

    // Check third action (index 2) - e.g., weapon action 2
    if (gAnalogTriggerThreshold < static_cast<float>(gActionValues[2] & gActionMask))
    {
        addPlayerAction(28, gActionValues[2]);
    }

    // Check fourth action (index 3) - using alt function
    if (gAnalogTriggerThreshold < static_cast<float>(gActionValues[3] & gActionMask))
    {
        addPlayerActionAlt(29, gActionValues[3]);
    }

    // Check fifth action (index 4) - alt function
    if (gAnalogTriggerThreshold < static_cast<float>(gActionValues[4] & gActionMask))
    {
        addPlayerActionAlt(30, gActionValues[4]);
    }

    // Check sixth action (index 5) - alt function
    if (gAnalogTriggerThreshold < static_cast<float>(gActionValues[5] & gActionMask))
    {
        addPlayerActionAlt(32, gActionValues[5]);
    }

    // Clear all buffered action values
    gActionValues[0] = 0;
    gActionValues[1] = 0;
    gActionValues[2] = 0;
    gActionValues[3] = 0;
    gActionValues[4] = 0;
    gActionValues[5] = 0;
}