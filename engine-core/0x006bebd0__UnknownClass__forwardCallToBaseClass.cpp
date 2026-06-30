// FUNC_NAME: UnknownClass::forwardCallToBaseClass
// Function address: 0x006bebd0
// Role: Thunk that adjusts 'this' by offset 0x1c (size of a base class subobject) and delegates to a base class method (FUN_006beb80).
// This is typical of a derived class member function that calls the base class implementation when multiple inheritance is used.
void __thiscall forwardCallToBaseClass(void* thisPtr, unsigned int param)
{
    // The base class subobject is located at offset 0x1c from the derived object.
    // Call the base class method (FUN_006beb80) with the adjusted this pointer.
    FUN_006beb80(reinterpret_cast<char*>(thisPtr) + 0x1c, param);
}