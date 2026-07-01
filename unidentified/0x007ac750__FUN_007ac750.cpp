// FUNC_NAME: UnknownClass::setFloatMember
void __thiscall UnknownClass::setFloatMember(float newValue) {
    // Compare with current float at +0x54
    if (newValue != this->someFloat) {
        // Set dirty flag at +0x64 (offset 100) to 1
        this->dirtyFlag = true;
        // Update the float member at +0x54
        this->someFloat = newValue;
    }
}