// FUNC_NAME: SomeClass::setFloatProperty
void __thiscall SomeClass::setFloatProperty(void* this, float newValue) {
    if (newValue != *(float*)((int)this + 0x1c)) {
        *(byte*)((int)this + 0x28) = 1; // dirty flag set
        *(float*)((int)this + 0x1c) = newValue;
    }
}