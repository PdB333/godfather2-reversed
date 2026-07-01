// FUNC_NAME: BaseClass::InitializeVTable
void __fastcall BaseClass::InitializeVTable(undefined4* thisPtr) {
    // Set the vtable pointer to the base class vtable
    *thisPtr = (undefined4)&PTR_LAB_00d73418;
}