// FUNC_NAME: SomeClass::getField9c
int SomeClass::getField9c() {
    // Returns the value at offset 0x9c from this pointer.
    // This is likely a member variable (e.g., a pointer or state).
    return *(int*)((char*)this + 0x9c);
}