// FUNC_NAME: SystemTable::callFunction
// Function address: 0x004e95e0
// This function retrieves a function pointer from a global table (base at DAT_012234c4)
// at offset 0x28, and invokes it with swapped argument order.
// Returns 0 if the pointer is null.

#include <cstdint>

// Global table pointer (likely a singleton in the EARS engine)
extern uint8_t* g_systemTable; // defined elsewhere, points to a structure

// Function pointer type: fastcall, two unsigned int args
typedef uint32_t (__fastcall* SystemTableFunc)(uint32_t arg1, uint32_t arg2);

uint32_t __fastcall FUN_004e95e0(uint32_t param_1, uint32_t param_2)
{
    // Retrieve function pointer at offset 0x28 from the global table
    SystemTableFunc* funcPtr = reinterpret_cast<SystemTableFunc*>(g_systemTable + 0x28);
    
    if (*funcPtr != nullptr)
    {
        // Call with arguments swapped: param_2 becomes first, param_1 becomes second
        return (*funcPtr)(param_2, param_1);
    }
    return 0;
}