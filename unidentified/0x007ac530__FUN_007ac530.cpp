// FUNC_NAME: SomeClass::setFloatProperty
void __thiscall SomeClass::setFloatProperty(float newValue) {
    if (newValue != this->m_floatProperty) { // +0x8: current float property value
        this->m_floatDirtyFlag = 1;           // +0x64: dirty flag (needs update)
        this->m_floatProperty = newValue;     // +0x8: update to new value
    }
}