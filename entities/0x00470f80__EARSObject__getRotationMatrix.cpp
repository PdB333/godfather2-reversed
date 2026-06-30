// FUNC_NAME: EARSObject::getRotationMatrix
// Address: 0x00470f80
// Copies the 4x4 rotation matrix from the object's transform, zeros translation, and validates position.
void __thiscall EARSObject::getRotationMatrix(Matrix4* outMatrix)
{
    // Copy the full 4x4 matrix from the object's transform data (offset +0xD0)
    // The matrix is stored as 16 floats in row-major order.
    float* src = reinterpret_cast<float*>(this + 0xD0);
    float* dst = outMatrix->data;
    for (int i = 0; i < 16; ++i)
    {
        dst[i] = src[i];
    }

    // Zero the translation components (indices 12, 13, 14) to extract pure rotation
    outMatrix->data[12] = 0.0f;
    outMatrix->data[13] = 0.0f;
    outMatrix->data[14] = 0.0f;

    // Check if the object's position (at offset +0x134) contains a valid (finite) value
    // The check uses a bitwise masking technique to detect NaN or infinity in each component.
    static const float kSubRef = DAT_00e2b1a4;       // value subtracted before bit manipulation
    static const uint kInfMask = DAT_00e44680;       // mask for exponent bits (likely 0x7F800000)
    static const float kThreshold = DAT_00e44598;    // small threshold for comparison

    float posX = *reinterpret_cast<float*>(this + 0x134);
    float posY = *reinterpret_cast<float*>(this + 0x138);
    float posZ = *reinterpret_cast<float*>(this + 0x13C);

    uint maskedX = reinterpret_cast<uint>(posX - kSubRef) & kInfMask;
    uint maskedY = reinterpret_cast<uint>(posY - kSubRef) & kInfMask;
    uint maskedZ = reinterpret_cast<uint>(posZ - kSubRef) & kInfMask;

    // If any component is non-finite (infinity or NaN), reset the matrix to identity
    if (static_cast<float>(maskedX) > kThreshold ||
        static_cast<float>(maskedY) > kThreshold ||
        static_cast<float>(maskedZ) > kThreshold)
    {
        FUN_0043a2a0(outMatrix, outMatrix); // setIdentity or normalizeMatrix
    }
}