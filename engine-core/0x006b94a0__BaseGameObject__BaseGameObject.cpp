// FUNC_NAME: BaseGameObject::BaseGameObject
void __thiscall BaseGameObject::BaseGameObject(void *thisObj)
{
    // Set primary vtable at +0x00
    *(int *)thisObj = (int)&PTR_FUN_00d5e618;
    // Set secondary vtable at +0x3C
    *(int *)((char *)thisObj + 0x3C) = (int)&PTR_LAB_00d5e608;
    // Set third vtable at +0x48
    *(int *)((char *)thisObj + 0x48) = (int)&PTR_LAB_00d5e604;
    // Construct subobject at offset +0x64 (param_1 + 0x19)
    FUN_004086d0((char *)thisObj + 0x64);
    // Initialize subobject
    FUN_00408310((char *)thisObj + 0x64);
    // Global initialization (e.g., registration with manager)
    FUN_0046c640();
}