// FUNC_NAME: SomeClass::setSixFloatBlock
// Function address: 0x006757a0
// Role: Copies 6 floats from input array to member at offsets 0x7C-0x90. If input is null, zeros first two floats only.

void __thiscall SomeClass::setSixFloatBlock(const float* data)
{
    if (data != nullptr)
    {
        *(float*)(this + 0x7C) = data[0];
        *(float*)(this + 0x80) = data[1];
        *(float*)(this + 0x84) = data[2];
        *(float*)(this + 0x88) = data[3];
        *(float*)(this + 0x8C) = data[4];
        *(float*)(this + 0x90) = data[5];
    }
    else
    {
        *(float*)(this + 0x7C) = 0.0f;
        *(float*)(this + 0x80) = 0.0f;
        // Note: remaining 4 floats at 0x84-0x90 are not cleared when data is null.
    }
}