// FUNC_NAME: SomeClass::CreateWithMemFlag
// Function address: 0x0076b190
// Role: Constructor that calls a base initializer (FUN_0076af90) and conditionally invokes a cleanup/destroy function (FUN_00624da0) based on the least significant bit of param_2.
// Returns the this pointer after construction.

SomeClass* __thiscall SomeClass::CreateWithMemFlag(SomeClass* this, byte flags) {
    // Call base class initialization (likely constructor or setup)
    this->InitializeBase();  // FUN_0076af90

    // If the lowest bit is set, perform a destructor/cleanup action (FUN_00624da0)
    if (flags & 1) {
        this->CleanupInternal();  // FUN_00624da0
    }

    return this;
}