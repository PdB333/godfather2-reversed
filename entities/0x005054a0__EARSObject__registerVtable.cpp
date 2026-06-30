// FUNC_NAME: EARSObject::registerVtable
// Function address: 0x005054a0
// Role: Derived class constructor helper that adds an entry to a function pointer table,
// then forwards remaining arguments to base class constructor (FUN_00508680).
// The object's first field (offset +0x00) is a pointer to a table structure.
// The table structure has a pointer to a current entry slot at offset +0x14.
// This function writes the address of a global function pointer array (PTR_LAB_01125034)
// into the current slot, then advances the slot pointer by 4 bytes.

#include <stdint.h>

// Forward declaration of base constructor; its address is 0x00508680
void __thiscall BaseClass::constructor(void* this, int32_t param2, int32_t param3, int64_t param4, int64_t param5, int32_t param6, int32_t param7, int32_t param8);

void __thiscall EARSObject::registerVtable(void* this, int32_t param2, int32_t param3, int64_t param4, int64_t param5, int32_t param6, int32_t param7, int32_t param8)
{
    // Obtain pointer to the function table (first field of the object)
    // this + 0x00: int32* m_pFunctionTable
    int32_t* functionTable = *(int32_t**)this;   // *this == this->m_pFunctionTable

    // Write the global vtable/function pointer array address into the current slot
    // functionTable + 0x14: int32** m_pCurrentSlot (pointer to a slot in the function table)
    **(int32_t**)((int8_t*)functionTable + 0x14) = (int32_t*)&PTR_LAB_01125034;

    // Advance m_pCurrentSlot by 4 bytes (size of a function pointer)
    int32_t** slotPtr = (int32_t**)((int8_t*)functionTable + 0x14);
    *slotPtr = *slotPtr + 1;    // +1 because int32_t* increments by 4 bytes

    // Call base class constructor with all remaining arguments
    BaseClass::constructor(this, param2, param3, param4, param5, param6, param7, param8);
}