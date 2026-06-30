// FUNC_NAME: SomeClass::Constructor
// Address: 0x00738430
// Role: Constructor with optional memory allocation based on flag.
// Calls base constructor FUN_00735560, then if param2 bit 0 set, allocates 0x26a0 bytes.

#include <cstdint>

// Forward declarations of callees
void __thiscall FUN_00735560();  // Base class initialization
uint32_t __thiscall FUN_0043b960(void* this, uint32_t size); // Allocation? Returns handle?

// Reconstructed constructor
uint32_t __thiscall SomeClass::Constructor(uint8_t initFlags)
{
    // Call base constructor/prologue
    FUN_00735560();

    // If the low bit of initFlags is set, allocate additional memory of size 0x26a0
    if ((initFlags & 1) != 0)
    {
        // Likely allocates or registers something with the given size (0x26a0)
        FUN_0043b960(this, 0x26a0);
    }

    return reinterpret_cast<uint32_t>(this);
}