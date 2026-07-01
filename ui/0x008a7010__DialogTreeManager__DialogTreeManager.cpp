// FUNC_NAME: DialogTreeManager::DialogTreeManager
undefined4 * __thiscall DialogTreeManager::DialogTreeManager(undefined4 *this, undefined4 baseInitParam)
{
    // Call base class constructor
    FUN_0046c590(baseInitParam);

    // Set vtable pointer (main class virtual table)
    *this = &PTR_FUN_00d79b38;
    // Set secondary vtable pointer (interface or second inheritance, offset +0x3c)
    this[0xf] = &PTR_LAB_00d79b28;
    // Set tertiary vtable pointer (offset +0x48)
    this[0x12] = &PTR_LAB_00d79b24;

    // Zero out a block of 17 DWORDs starting at offset +0x50 (index 0x14) through +0x94 (index 0x25)
    for (int i = 0x14; i <= 0x25; i++) {
        this[i] = 0;
    }

    return this;
}