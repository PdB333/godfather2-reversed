// FUNC_NAME: SomeClass::setParamField
void __thiscall SomeClass::setParamField(SomeClass* this, uint32_t value) {
    // +0x88: stores a generic parameter (likely a pointer or ID)
    *(uint32_t*)((uint32_t)this + 0x88) = value;
}