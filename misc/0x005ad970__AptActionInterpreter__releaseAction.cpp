// FUNC_NAME: AptActionInterpreter::releaseAction
// Address: 0x005ad970
// Releases an action at the current index (0-63) from the action interpreter.
// Calls the action's virtual release function and decrements the action count.

#include <cstdint>

// Forward declarations for called functions
void FUN_005a0d00(int);          // Likely lock/enter critical section
int  FUN_005a8fe0();             // Returns current action index
void FUN_005a6ff0();             // Unknown cleanup function

// Global data (from Ghidra)
extern uint32_t DAT_0119a9cc;    // Pointer to AptActionInterpreter instance
extern uint32_t DAT_0119cbbc;    // Return value (success flag)
extern uint32_t DAT_01128fe8;    // Debug assertion flag
extern void*    DAT_0103aee0;    // Vtable for action types (array of function pointers)

// Simplified assertion macro (original uses EA debug system)
#define ASSERT(cond, msg, file, line) \
    if (!(cond)) { /* debug break */ }

uint32_t AptActionInterpreter::releaseAction()
{
    // Lock or enter critical section
    FUN_005a0d00(0);

    int nIndex = FUN_005a8fe0(); // Get current action index
    if (nIndex < 0 || nIndex >= 64)
    {
        // Assertion failure
        ASSERT(false, "nIndex >= 0 && nIndex < 64", "..\\source\\Apt\\AptActionInterpreter.cpp", 0x367);
        // Debug break if assertion flag is set
        if (DAT_01128fe8 != 0)
        {
            // ... debug handling (omitted for brevity)
        }
    }

    // Calculate offset into action array (each entry is 0x2C bytes)
    int offset = nIndex * 0x2C;
    uint32_t base = DAT_0119a9cc;

    // Check if action object pointer at base+0x2518 is non-null
    if (*(int*)(base + offset + 0x2518) != 0)
    {
        // Get pointer to action type identifier (uint)
        uint32_t* pActionType = *(uint32_t**)(base + offset + 0x251C);
        // Use low 15 bits as index into vtable to call release function
        uint32_t typeIndex = (*pActionType) & 0x7FFF;
        void (*releaseFunc)(uint32_t*) = ((void (**)(uint32_t*))&DAT_0103aee0)[typeIndex];
        releaseFunc(pActionType);

        // Decrement reference count? (offset 0x2528)
        int refCount = *(int*)(base + offset + 0x2528);
        for (int i = 0; i < refCount; i++)
        {
            FUN_005a6ff0(); // Unknown cleanup
        }

        // Clear action object pointer
        *(int*)(base + offset + 0x2518) = 0;

        // Decrement total action count at base+0x3018
        (*(int*)(base + 0x3018))--;
    }

    return DAT_0119cbbc;
}