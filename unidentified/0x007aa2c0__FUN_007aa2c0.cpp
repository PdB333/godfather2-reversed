// FUNC_NAME: SomeClass::setVector4ArrayElement
// Function address: 0x007aa2c0
// Copies a 16-byte (4x undefined4) value from source into an array element at this+0x1c + index*0x10
// Assumes the array element is a Vector4 (4 floats) or similar 16-byte structure.
void __thiscall SomeClass::setVector4ArrayElement(int index, const float* source)
{
    float* dest = (float*)(this + 0x1c + index * 0x10);
    dest[0] = source[0];
    dest[1] = source[1];
    dest[2] = source[2];
    dest[3] = source[3];
}