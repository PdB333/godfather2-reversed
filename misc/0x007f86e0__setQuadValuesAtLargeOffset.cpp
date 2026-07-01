// FUNC_NAME: setQuadValuesAtLargeOffset
void __thiscall SomeClass::setQuadValues(SomeClass* this, const int* values)
{
    // Write four consecutive 4-byte values to high offsets (likely part of a larger data structure)
    *(int*)((uintptr_t)this + 0x1b98) = values[0];  // +0x1b98
    *(int*)((uintptr_t)this + 0x1b9c) = values[1];  // +0x1b9c
    *(int*)((uintptr_t)this + 0x1ba0) = values[2];  // +0x1ba0
    *(int*)((uintptr_t)this + 0x1ba4) = values[3];  // +0x1ba4
}