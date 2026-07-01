// FUNC_NAME: UnknownClass::Constructor
void* __fastcall UnknownClass::Constructor(void* thisPtr) {
    // Set vtable pointer (class vtable at 0x00d748f8)
    *(int*)thisPtr = (int)&PTR_LAB_00d748f8;

    // Initialize 7 sub-objects (likely an array of 7 members or base classes)
    // Each call to FUN_005953b0 initializes one sub-object.
    // The sub-objects are probably at offsets 0x4, 0x8, ... from thisPtr.
    FUN_005953b0(); // sub-object 0
    FUN_005953b0(); // sub-object 1
    FUN_005953b0(); // sub-object 2
    FUN_005953b0(); // sub-object 3
    FUN_005953b0(); // sub-object 4
    FUN_005953b0(); // sub-object 5
    FUN_005953b0(); // sub-object 6

    return thisPtr;
}