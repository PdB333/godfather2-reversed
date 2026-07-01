// FUNC_NAME: SomeClass::getSomeField
int __fastcall getSomeField(int thisPtr)
{
    // Returns the value at offset -0x10 from the given pointer.
    // This is likely a field accessor for a member at a negative offset,
    // possibly a vtable pointer or a base class offset.
    return *(int *)(thisPtr - 0x10);
}