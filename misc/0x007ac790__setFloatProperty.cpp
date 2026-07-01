//FUNC_NAME: setFloatProperty
// Function address: 0x007ac790
// Role: Setter for a float member with dirty flag update.
// Offsets: float member at +0x5c, dirty flag (byte) at +0x64

void __thiscall setFloatProperty(float newValue)
{
    if (newValue != *(float *)(this + 0x5c))
    {
        *(uint8 *)(this + 0x64) = 1; // mark dirty
        *(float *)(this + 0x5c) = newValue;
    }
}