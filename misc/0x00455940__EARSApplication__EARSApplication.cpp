// FUNC_NAME: EARSApplication::EARSApplication
void __thiscall EARSApplication::EARSApplication(EARSApplication* this)
{
    // +0x00: vtable pointer (set to base class vtable)
    *this = (undefined4*)&PTR_FUN_00e31970;
    // +0x08: secondary vtable / base class descriptor (initial base)
    this[2] = (undefined4*)&PTR_LAB_00e3197c;
    // Call virtual function (index 0xC) on an object stored at offset +0x0C
    // The object pointer is this[3]; its vtable is obtained and method at +0xC called
    (**(code **)(*(int *)this[3] + 0xc))();
    // +0x08: switch to derived class vtable/descriptor
    this[2] = (undefined4*)&PTR_LAB_00e31980;
    // Global flag: application initialization state
    DAT_01223450 = 0;
    // Additional subsystem initialization
    FUN_0049c640();
}