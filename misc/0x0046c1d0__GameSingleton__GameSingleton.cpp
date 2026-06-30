// FUNC_NAME: GameSingleton::GameSingleton
__thiscall GameSingleton::GameSingleton(uint32_t* this)
{
    uint32_t** vtable2Slot = reinterpret_cast<uint32_t**>(this + 1); // +0x04
    *vtable2Slot = (uint32_t*)&PTR_FUN_00e2f19c; // set vtable for second base class
    this[2] = 1; // +0x08: reference count or initialization flag
    this[3] = 0; // +0x0C: zero-initialized field
    this[0] = (uint32_t)&PTR_FUN_00e327f0; // +0x00: primary vtable (first base)
    *vtable2Slot = (uint32_t*)&PTR_LAB_00e327f4; // +0x04: override vtable for derived class
    this[4] = 0; // +0x10: another field

    g_pGlobalSingleton = this; // _DAT_0122347c: store static singleton pointer

    if (g_OldSingleton != 0) // DAT_012069d4: check if previous instance exists
    {
        // Release or clean up the old singleton via vtable slot at +0x04
        FUN_00407e60(vtable2Slot, &g_OldSingleton);
    }
    return this;
}