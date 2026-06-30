// FUNC_NAME: SomeClass::setSubObjectIntField
void __thiscall SomeClass::setSubObjectIntField(int value)
{
    // Write `value` to offset +8 of the object pointed to by this->+0x18
    *(int *)(*(int *)(this + 0x18) + 8) = value;
}