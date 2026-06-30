// FUNC_NAME: EARSObjectBase::EARSObjectBase
// Address: 0x00441aa0 - Base constructor for EARS engine objects, sets vtable and calls initialization chain
void __fastcall EARSObjectBase::EARSObjectBase(EARSObjectBase* thisObj)
{
    // Set virtual function table pointer at +0x00
    thisObj->vtable = (void**)&PTR_FUN_00e310ac;

    // Initialize field at +0x08 with a label pointer (possibly a subclass or state object)
    thisObj->field_0x08 = (void*)&PTR_LAB_00e310b8;

    // Call external initialization function with a reference to another structure
    // This likely initializes internal subsystems or subobjects
    FUN_0049c7f0(&PTR_LAB_00e310a0);

    // Replace field at +0x08 with a different label pointer
    thisObj->field_0x08 = (void*)&PTR_LAB_00e310bc;

    // Reset a global flag (possibly a singleton initialized indicator)
    g_SomeGlobalFlag = 0;

    // Call final initialization step
    FUN_0049c640();
}