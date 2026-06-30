// FUNC_NAME: ERSObject::setTransformMatrix
void __thiscall ERSObject::setTransformMatrix(const float (*sourceMatrix)[4]) // source is 4x4 float array
{
    // Copy 16 floats (4x4 matrix) from source to this object's internal transform (stored at +0x30)
    // The matrix is stored as sequential floats, row-major (or column-major, game-dependent)
    // Offsets: +0x30 to +0x6C = 64 bytes (16 floats)

    float* destMatrix = reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(this) + 0x30);
    const float* src = reinterpret_cast<const float*>(sourceMatrix);

    for (int i = 0; i < 16; ++i)
    {
        destMatrix[i] = src[i];
    }
}