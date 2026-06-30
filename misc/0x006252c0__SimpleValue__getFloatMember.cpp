// FUNC_NAME: SimpleValue::getFloatMember
// Function address: 0x006252c0
// Retrieves a float value from offset 0x4 of the object (likely a data member after vtable pointer at offset 0x0).
float SimpleValue::getFloatMember() __thiscall {
    return *(float*)((uintptr_t)this + 4);
}