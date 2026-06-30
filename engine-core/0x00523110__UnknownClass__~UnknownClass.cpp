// FUNC_NAME: UnknownClass::~UnknownClass
// Address: 0x00523110
// Role: Destructor with optional deallocation based on flag.
// Calls base destruction (FUN_005231b0) then conditionally deletes memory (FUN_009c8eb0) if flag bit 0 is set.
// This pattern is typical for MSVC destructors where the second parameter (byte) indicates whether to call operator delete.

UnknownClass * __thiscall UnknownClass::~UnknownClass(UnknownClass *this, byte deleteFlag)
{
    this->destructSubroutine(); // FUN_005231b0 - actual destruction logic (e.g., releasing resources)
    if ((deleteFlag & 1) != 0) {
        operatorDelete(this); // FUN_009c8eb0 - likely operator delete or placement delete
    }
    return this; // MSVC destructors often return 'this' for chaining
}