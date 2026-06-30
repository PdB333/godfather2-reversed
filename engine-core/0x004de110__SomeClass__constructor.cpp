// FUNC_NAME: SomeClass::constructor
// Address: 0x004de110
// Role: Constructor with optional deallocation flag

SomeClass* __thiscall SomeClass::constructor(SomeClass* thisPtr, byte allocFlag)
{
    // Call base constructor/initializer
    baseConstructor(); // FUN_004de130 - likely initializes base members

    // If the 'alloc' flag indicates memory was allocated externally,
    // call the cleanup function (operator delete or destructor)
    if ((allocFlag & 1) != 0) {
        deallocateMemory(thisPtr); // FUN_009c8eb0 - frees memory
    }

    return thisPtr;
}