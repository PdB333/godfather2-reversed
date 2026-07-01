// FUNC_NAME: SomeClass::setFloatWithCallback
void __thiscall SomeClass::setFloatWithCallback(float newValue) {
    // Offset +0x130: pointer to a callback object (likely a script binding or delegate)
    // Offset +0xf04: current stored float value
    if (this->callbackObject != nullptr && this->storedFloat != newValue) {
        // Call virtual function at vtable +0x4c (likely "onChange" or "setProperty")
        // The constant 0x555eec2b is a message ID or property hash
        // The callback may return a modified newValue (stored in ESI register after call)
        newValue = this->callbackObject->onPropertyChanged(0x555eec2b, newValue);
    }
    this->storedFloat = newValue;
}