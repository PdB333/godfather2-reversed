// FUNC_NAME: GameObject::setActive
// Function at 0x006b2600: Sets a flag at offset 0x34 bit 2 and logs the change
void __thiscall GameObject::setActive(bool enable)
{
    // Setup vtable pointer (likely part of base class initialization)
    void** vtablePtr = &PTR_LAB_00d5dbb0; // vtable for this object? (stored but unused)
    int* flags = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x34); // +0x34: flags field
    uint32_t stringId; // ID for debug string (global strings)

    // Clear unused local variables to avoid compiler warnings
    uint8_t unused = 0;
    if (enable)
    {
        *flags |= 4; // Set bit 2 (value 4)
        stringId = DAT_0112a5f0; // "Enabled" string?
        FUN_00408a00(&stringId, 0); // Log the change
        return;
    }
    *flags &= ~4; // Clear bit 2
    stringId = DAT_0112a5e8; // "Disabled" string?
    FUN_00408a00(&stringId, 0);
}