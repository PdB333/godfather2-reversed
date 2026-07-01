// FUNC_NAME: PlayerSM::updateStateMachine
// Address: 0x009276a0
// Reconstructed from Ghidra decompilation
// This function updates a player state machine with substates and timer.
// param_1: this pointer to state machine struct (m_state, m_subState, m_timer)
// param_2: pointer to Player object with flags at offsets 0x3c4-0x3c8
// param_3: additional boolean flag (e.g., force reset)

#include <cstdint>

// Forward declarations of condition check functions
bool FUN_009275a0(); // e.g., isPlayerInCar?
bool FUN_00927600(); // e.g., isPlayerOnFoot?
bool FUN_00927620(); // e.g., isPlayerInCover?
bool FUN_009275c0(); // e.g., isPlayerInCombat?

// Global constants
extern float DAT_00d87aa4; // threshold timer for reset
extern float DAT_01206800; // timer increment per frame

int __thiscall PlayerSM::updateStateMachine(int* thisPtr, int* playerObj, char forceReset)
{
    int currentSubState = thisPtr[1]; // +0x04: m_subState
    bool flagA = false; // corresponds to bVar4
    bool flagB = false; // corresponds to bVar2
    bool flagC = false; // corresponds to bVar3

    // Player flags at offsets from playerObj
    // +0x3c4: m_isInVehicle
    // +0x3c5: m_isOnFoot
    // +0x3c6: m_isInCover
    // +0x3c7: m_isInCombat
    // +0x3c8: m_isInCar (or m_isInCarAsPassenger?)
    char* flags = (char*)playerObj;

    // Determine flags based on current state
    if (thisPtr[0] == 1) // state 1 (e.g., GROUND)
    {
        // flagA: not in combat AND on foot
        flagA = (flags[0x3c7] == 0) && (flags[0x3c5] != 0);
        // flagB: not in combat OR on foot (inverted logic)
        flagB = (flags[0x3c7] == 0) || (flags[0x3c5] != 0);
        // flagC: not in car AND in cover
        flagC = (flags[0x3c8] == 0) && (flags[0x3c6] != 0);
    }
    else if (thisPtr[0] == 2) // state 2 (e.g., COVER)
    {
        // flagC: not in combat AND on foot (note: same as flagA for state1)
        flagC = (flags[0x3c7] == 0) && (flags[0x3c5] != 0);
        // flagA: not in car AND in cover
        flagA = (flags[0x3c8] == 0) && (flags[0x3c6] != 0);
        // flagB: not in car OR in cover (inverted)
        flagB = (flags[0x3c8] == 0) || (flags[0x3c6] != 0);
    }

    // Check for reset conditions: subState == 4 OR (subState > 0 AND (timer exceeded OR in vehicle OR forceReset))
    if ((currentSubState == 4) ||
        ((currentSubState > 0) &&
         ((DAT_00d87aa4 < (float)thisPtr[2]) || (flags[0x3c4] != 0) || (forceReset != 0))))
    {
        // Reset state machine
        thisPtr[0] = 0; // m_state = 0
        thisPtr[1] = 0; // m_subState = 0
        thisPtr[2] = 0; // m_timer = 0.0f
        goto default_case;
    }

    // State machine transitions based on current subState
    switch (currentSubState)
    {
    case 0: // initial substate
    {
        char result1 = FUN_009275a0();
        if (((result1 == 0) || (result1 = FUN_00927600(), result1 != 0)) ||
            (result1 = FUN_00927620(), result1 != 0))
        {
            // If any condition fails, try alternative path
            result1 = FUN_00927600();
            if (((result1 == 0) || (result1 = FUN_009275a0(), result1 != 0)) ||
                (result1 = FUN_009275c0(), result1 != 0))
            {
                goto default_case;
            }
            // Set state to 2 (e.g., COVER)
            thisPtr[0] = 2;
        }
        else
        {
            // Set state to 1 (e.g., GROUND)
            thisPtr[0] = 1;
        }
        thisPtr[1] = 1; // subState = 1
        goto default_case;
    }
    case 1: // substate 1
        if (flagB) // condition to advance
        {
            thisPtr[1] = 2;
            goto default_case;
        }
        break;
    case 2: // substate 2
        if (flagA) // condition to advance
        {
            thisPtr[1] = 3;
            goto default_case;
        }
        break;
    case 3: // substate 3
        if (flagB) // condition to advance
        {
            thisPtr[1] = 4;
            goto default_case;
        }
        break;
    default:
        goto default_case;
    }

    // If no transition occurred, check for reset via flagC
    if (flagC)
    {
        thisPtr[0] = 0;
        thisPtr[1] = 0;
        thisPtr[2] = 0;
    }

default_case:
    // If subState unchanged, accumulate timer; else reset timer and signal change
    if (currentSubState == thisPtr[1])
    {
        thisPtr[2] = (int)((float)thisPtr[2] + DAT_01206800); // timer += frame increment
        return 0; // no state change
    }
    else
    {
        thisPtr[2] = 0; // reset timer
        return 1; // state changed
    }
}