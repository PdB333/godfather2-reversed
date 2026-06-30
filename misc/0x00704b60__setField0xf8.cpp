// FUNC_NAME: setField0xf8
// Address: 0x00704b60
// Role: Simple setter writing an integer value to offset +0xF8 in the object.
// Likely a member function setting a state, ID, or pointer/handle field.

void __thiscall setField0xf8(int value)
{
    *(int*)(this + 0xF8) = value; // +0xF8: unknown field
}