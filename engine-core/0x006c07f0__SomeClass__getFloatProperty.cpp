// FUNC_NAME: SomeClass::getFloatProperty
float SomeClass::getFloatProperty() const
{
    // +0x10: float member (e.g., speed, angle, or other scalar)
    return *(float*)((uint8_t*)this + 0x10);
}