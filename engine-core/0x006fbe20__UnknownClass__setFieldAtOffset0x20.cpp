// FUNC_NAME: UnknownClass::setFieldAtOffset0x20
void __thiscall UnknownClass::setFieldAtOffset0x20(int this, int value) {
    // +0x20: a 32-bit integer or pointer field
    *(int *)(this + 0x20) = value;
}