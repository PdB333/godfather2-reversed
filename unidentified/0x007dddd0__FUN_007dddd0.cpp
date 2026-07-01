// FUNC_NAME: UnknownClass::constructor
// Function at 0x007dddd0: Constructor initializing object with two-phase vtable setup
void __thiscall UnknownClass::constructor(UnknownClass* this) // param_1 is 'this'
{
    // Set vtable to base class vtable (first phase)
    this->vtable = (void**)&PTR_LAB_00d6f5e8; // Base class vtable pointer
    FUN_007f6420(0x29); // Initialize base class with parameter 0x29 (likely a resource ID or type)

    // Set vtable to derived class vtable (second phase)
    this->vtable = (void**)&PTR_LAB_00d6b95c; // Derived class vtable pointer
    FUN_0080ea60(); // Final initialization for derived class

    return;
}