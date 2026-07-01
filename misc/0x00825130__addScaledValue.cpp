// FUNC_NAME: addScaledValue
void __thiscall SomeClass::addScaledValue(SomeClass* target, float factor)
{
    // Update the float at offset 0x4C with a weighted addition from target's same offset.
    // This is likely used for linear blending or integration (e.g., position += velocity * dt).
    this->field_0x4C = target->field_0x4C * factor + this->field_0x4C;
}