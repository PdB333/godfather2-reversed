// FUNC_NAME: ProcessPendingStateTransitions
// Address: 0x006915e0
// Role: Checks pending state transitions for a given slot. Reads primary/secondary state from global manager,
// compares with target states stored in arrays, and either triggers transition (if current state matches)
// or removes the target from pending lists (if not matching, presumably already handled).
// This uses two separate pending lists and two target arrays, likely for different state systems (e.g., movement and action).

#include <cstddef>

// External globals (from Ghidra)
extern int* g_pStateManager;                 // DAT_012233b4 - pointer to state manager object (singleton)
extern int g_primaryTargetStates[];           // DAT_01129bd4 - array of target state IDs for primary (indexed by slotIndex*2)
extern int g_secondaryTargetStates[];          // DAT_01129bd0 - array of target state IDs for secondary
extern int g_primaryPendingList[];             // DAT_00e50658 - pending list for primary transitions
extern int g_primaryPendingCount;              // DAT_00e50698 - count of entries in primary pending list
extern int g_secondaryPendingList[];           // DAT_00e50610 - pending list for secondary transitions
extern int g_secondaryPendingCount;            // DAT_00e50650 - count of entries in secondary pending list

// External functions (from other modules)
extern void SetProcessingState(char state);   // FUN_00411070 - presumably marks state as being processed
extern int GetCurrentState(void);             // FUN_004958a0 - returns current state ID
extern void HandlePrimaryStateTransition(int slotIndex);   // FUN_006914a0 - perform primary transition for slot
extern void HandleSecondaryStateTransition(int slotIndex); // FUN_00691530 - perform secondary transition for slot

void ProcessPendingStateTransitions(int slotIndex)
{
    // Offsets 0x564 and 0x565 in the state manager object hold the pending state IDs (char values)
    char primaryPendingState = *(char*)(g_pStateManager + 0x564);
    char secondaryPendingState = *(char*)(g_pStateManager + 0x565);

    // --- Primary state handling ---
    if (primaryPendingState != 0x12) // 0x12 is likely "no pending state"
    {
        int targetPrimary = g_primaryTargetStates[slotIndex * 2]; // target state for this slot
        SetProcessingState(primaryPendingState); // mark this state as being processed
        int currentState = GetCurrentState();

        if (currentState == targetPrimary)
        {
            // Current state matches target -> perform the transition
            HandlePrimaryStateTransition(slotIndex);
        }
        else
        {
            // Remove targetPrimary from the primary pending list (if present)
            int count = g_primaryPendingCount;
            if (count > 0)
            {
                int i;
                for (i = count - 1; i >= 0; i--)
                {
                    if (g_primaryPendingList[i] == targetPrimary)
                    {
                        // Shift elements left to fill the gap
                        if (i < count - 1)
                        {
                            for (int j = i; j < count - 1; j++)
                            {
                                g_primaryPendingList[j] = g_primaryPendingList[j + 1];
                            }
                        }
                        g_primaryPendingCount--;
                        break;
                    }
                }
            }
        }
    }

    // --- Secondary state handling ---
    if (secondaryPendingState != 0x12)
    {
        int targetSecondary = g_secondaryTargetStates[slotIndex * 2];
        SetProcessingState(secondaryPendingState);
        int currentState = GetCurrentState();

        if (currentState == targetSecondary)
        {
            HandleSecondaryStateTransition(slotIndex);
        }
        else
        {
            int count = g_secondaryPendingCount;
            if (count > 0)
            {
                int i;
                for (i = count - 1; i >= 0; i--)
                {
                    if (g_secondaryPendingList[i] == targetSecondary)
                    {
                        if (i < count - 1)
                        {
                            for (int j = i; j < count - 1; j++)
                            {
                                g_secondaryPendingList[j] = g_secondaryPendingList[j + 1];
                            }
                        }
                        g_secondaryPendingCount--;
                        break;
                    }
                }
            }
        }
    }
}