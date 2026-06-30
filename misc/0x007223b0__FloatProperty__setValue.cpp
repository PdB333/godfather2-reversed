// FUNC_NAME: FloatProperty::setValue
// Function at 0x007223b0 - Set a float field with dirty flag. If the new value differs from the current value at +0x24, mark the byte at +0x28 as 1 and update the float.
void __thiscall FloatProperty::setValue(int this, float newValue)
{
    // Compare with current value at offset +0x24
    if (newValue != *(float *)(this + 0x24))
    {
        // Set dirty flag at +0x28 to indicate change
        *(unsigned char *)(this + 0x28) = 1;
        // Update stored float at +0x24
        *(float *)(this + 0x24) = newValue;
    }
}