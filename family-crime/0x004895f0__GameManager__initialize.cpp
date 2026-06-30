// FUNC_NAME: GameManager::initialize

void __thiscall GameManager::initialize(GameManager *this)
{
    // Set up virtual function tables for the object
    // +0x00: Main vtable pointer (class-specific)
    *this = (GameManager *)&PTR_FUN_00e337f8;
    // +0x08: Secondary vtable pointer (likely base class or interface)
    this->field_8 = &PTR_LAB_00e33804;

    // Register or call a base initialization routine via a callback/label
    // The second parameter (0x00489420) might be the address of the base class constructor
    FUN_00607d50(0, (void *)0x00489420);

    // Initialize member fields to zero / null
    // +0x14: Some integer/pointer field
    this->field_14 = 0;
    // +0x10: Pointer field; release previous if non-null, then set to null
    if (this->field_10 != 0) {
        FUN_009c8f10(this->field_10);
    }
    this->field_10 = 0;
    // +0x18: Another integer field
    this->field_18 = 0;

    // Call a virtual function on the base sub-object (offset +0x0C from base vtable)
    // The base sub-object is located at this->field_C (offset +0x0C)
    (*(void (__thiscall **)(void *))(*(int *)this->field_C + 0xC))(this->field_C);

    // Clean up again (possibly reentrant cleanup)
    if (this->field_10 != 0) {
        FUN_009c8f10(this->field_10);
    }

    // Update the secondary vtable pointer to a final one (likely after base class init)
    this->field_8 = &PTR_LAB_00e33808;

    // Set a global flag to indicate the manager is ready (address 0x0122349c)
    DAT_0122349c = 0;

    // Final engine startup routine (e.g., register systems, start threads)
    FUN_0049c640();

    return;
}