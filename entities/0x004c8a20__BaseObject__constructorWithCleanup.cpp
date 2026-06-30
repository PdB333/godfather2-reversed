// FUNC_NAME: BaseObject::constructorWithCleanup
// Function address: 0x004c8a20
// Role: Initializes an object and optionally performs cleanup if the flag's bit 0 is set.
// This is a constructor-like method that calls an initialization function and then conditionally
// calls a destructor-like function (e.g., for placement new/delete semantics).
undefined4 __thiscall BaseObject::constructorWithCleanup(BaseObject *this, byte cleanupFlag) {
    // Call the internal initialization routine (likely a base constructor or init method)
    this->init(); // FUN_004c8a80 - member function, no arguments, uses same this

    // If the lowest bit of cleanupFlag is set, perform cleanup/destruction
    if ((cleanupFlag & 1) != 0) {
        // This function likely releases resources or calls a destructor on the object
        BaseObject::cleanup(this); // FUN_009c8eb0 - static or member function taking this pointer
    }

    // Return the pointer to the object (typical for C++ constructor thunk)
    return (undefined4)this;
}