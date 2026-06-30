// FUNC_NAME: Entity::setVector4
void __thiscall Entity::setVector4(int thisPtr, const float* source) // source: pointer to 4 floats
{
    // Copy a 4-component vector (float[4]) into the object's internal storage at +0x10
    *(float*)(thisPtr + 0x10) = source[0];  // +0x10: x component
    *(float*)(thisPtr + 0x14) = source[1];  // +0x14: y component
    *(float*)(thisPtr + 0x18) = source[2];  // +0x18: z component
    *(float*)(thisPtr + 0x1c) = source[3];  // +0x1c: w component or padding
}