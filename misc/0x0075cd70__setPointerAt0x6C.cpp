// FUNC_NAME: setPointerAt0x6C
void __thiscall SomeClass::setPointerAt0x6C(void* this, void* value) {
    // Store value at offset +0x6C (likely a pointer or integer member)
    *(void**)((char*)this + 0x6C) = value;
}