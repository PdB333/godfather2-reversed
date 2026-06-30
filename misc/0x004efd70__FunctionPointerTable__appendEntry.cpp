// FUNC_NAME: FunctionPointerTable::appendEntry
// Function address: 0x004efd70
// This function appears to be a method of a class that manages a table of function pointers.
// It writes a specific function pointer (PTR_FUN_01124cc4) into the current slot of the table,
// then advances the slot pointer by 4 bytes. It then calls another function (FUN_004f07e0) with a
// rearranged parameter order, likely a forwarding or thunking operation.

void __thiscall FunctionPointerTable::appendEntry(
    int *thisPtr,               // +0x00: pointer to table control block
    uint32_t param2,            // passed to forwarded function
    uint32_t param3,            // reordered later
    uint32_t param4,            // reordered to last position
    uint64_t param5,            // passed third
    uint64_t param6,            // passed fourth
    uint64_t param7,            // passed fifth
    uint64_t param8,            // passed sixth
    uint32_t param9,            // passed seventh
    uint32_t param10)           // passed eighth
{
    int *tablePtr = *thisPtr;                                      // dereference this to get table base
    uint32_t *slotPtr = *(uint32_t **)(tablePtr + 0x14);           // +0x14: pointer to current slot in function pointer array
    *slotPtr = (uint32_t)&PTR_FUN_01124cc4;                        // write address of function pointer constant into slot
    uint32_t *nextSlotPtr = (uint32_t *)(tablePtr + 0x14);         
    *nextSlotPtr = (uint32_t)(slotPtr + 1);                        // advance slot pointer by 4 (one function pointer entry)
    // Forward call with rearranged parameters (likely due to differing calling conventions or thunking)
    FUN_004f07e0(param2, param5, param6, param7, param8, param3, param9, param10, param4);
    return;
}