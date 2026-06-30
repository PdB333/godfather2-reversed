// FUNC_NAME: SomeClass::SetField8
void __thiscall SomeClass::SetField8(int value) {
    // store value at offset 0x8 (likely some integer property)
    *(int *)(this + 8) = value;
}