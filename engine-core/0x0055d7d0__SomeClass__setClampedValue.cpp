// FUNC_NAME: SomeClass::setClampedValue
void __thiscall SomeClass::setClampedValue(int this, uint value)
{
    // Clamp value to range [0, 15] (0x0 to 0xF)
    if (value == 0) {
        *(int *)(this + 0x114) = 0;
        return;
    }
    if (value > 0xe) {
        value = 0xf;
    }
    *(uint *)(this + 0x114) = value;
}