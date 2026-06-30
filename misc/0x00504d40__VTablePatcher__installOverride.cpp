// FUNC_NAME: VTablePatcher::installOverride
void __thiscall VTablePatcher::installOverride(void *this, uint32_t param2, uint32_t param3, uint64_t param4, uint64_t param5, uint32_t param6, uint32_t param7, uint32_t param8)
{
    // Dereference this to get the vtable pointer (this points to an object whose first field is its vtable)
    uint32_t *vtablePtr = *(uint32_t **)this;

    // At offset +0x14 in the vtable is a pointer to an entry list (array of function pointers)
    uint32_t *entryListPtr = (uint32_t *)(vtablePtr + 0x14); // +0x14: pointer to current entry slot
    uint32_t **currentEntry = (uint32_t **)(*entryListPtr); // Pointer to the entry slot

    // Overwrite the current entry with a new function pointer (PTR_LAB_01124ff8)
    *currentEntry = (uint32_t *)&PTR_LAB_01124ff8; // Likely a hook/trampoline function

    // Advance the entry list pointer by 4 bytes (size of a function pointer)
    *entryListPtr += 4;

    // Forward all parameters (except this) to the original function being overridden
    FUN_005085d0(param2, param3, param4, param5, param6, param7, param8);
}