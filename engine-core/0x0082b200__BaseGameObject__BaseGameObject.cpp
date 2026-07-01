// FUNC_NAME: BaseGameObject::BaseGameObject
void __thiscall BaseGameObject::BaseGameObject(BaseGameObject* this)
{
    // Set vtable pointer for base class (vtable at offset 0x00)
    *(void**)this = (void*)&PTR_FUN_00d73820;
    // Call base constructor (likely sets base vtable and members)
    FUN_0082b1c0();
    // Override vtable entry at offset 0x30 (index 0xC) for derived behavior
    *(void**)((char*)this + 0x30) = (void*)&PTR_LAB_00e32854;
    // Call derived initialization routine
    FUN_00821f60();
    return;
}