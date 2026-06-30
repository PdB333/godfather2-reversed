// FUNC_NAME: SomeClass::getFieldPointer
// Returns a pointer to one of two member fields based on selector.
// Offsets: +0x68 (field A), +0x74 (field B)
// If selector == 1, returns pointer to field at +0x68; otherwise returns pointer to field at +0x74.
void* __thiscall SomeClass::getFieldPointer(int selector) {
    void* result = (void*)((int)this + 0x68);
    if (selector != 1) {
        result = (void*)((int)this + 0x74);
    }
    return result;
}