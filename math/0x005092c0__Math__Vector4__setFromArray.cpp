// FUNC_NAME: Math::Vector4::setFromArray
void __thiscall Math::Vector4::setFromArray(float *this, float *array)
{
    // Copies four floats from array into the Vector4's components at offsets +0x10, +0x14, +0x18, +0x1c
    // This suggests the Vector4 structure has a base size of 0x10 (likely other members or vtable pointer)
    float f0 = array[0];
    float f1 = array[1];
    float f2 = array[2];
    float f3 = array[3];
    this[0x4] = f0;  // +0x10: x component
    this[0x5] = f1;  // +0x14: y component
    this[0x6] = f2;  // +0x18: z component
    this[0x7] = f3;  // +0x1c: w component
}