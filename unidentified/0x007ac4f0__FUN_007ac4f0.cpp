// FUNC_NAME: SomeClass::setFloatAndMarkDirty
void __thiscall SomeClass::setFloatAndMarkDirty(float newValue) {
    // m_floatMember at +0x0 (float)
    // m_dirtyFlag at +0x64 (uint8_t, offset = 0x19 * sizeof(float) = 0x64)
    if (newValue != this->m_floatMember) {
        this->m_dirtyFlag = 1;
        this->m_floatMember = newValue;
    }
}