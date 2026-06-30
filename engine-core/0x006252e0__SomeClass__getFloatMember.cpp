// FUNC_NAME: SomeClass::getFloatMember
// Address: 0x006252e0
// Role: Simple getter for a float stored at offset +0x4 in the object.
// This is likely a cached value or a property accessed frequently.
float __thiscall SomeClass::getFloatMember(void) const
{
    // +0x4: float member (e.g., a scalar quantity like health, speed, or coordinate)
    return *(float *)((int)this + 4);
}