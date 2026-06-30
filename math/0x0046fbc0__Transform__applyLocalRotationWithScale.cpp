// FUNC_NAME: Transform::applyLocalRotationWithScale
void __thiscall Transform::applyLocalRotationWithScale(int *this, int transformType, float scaleFactor)
{
    // Copy current matrix (16 floats at offset 0x34) to local buffer // +0x34 = matrix[16]
    float localMatrix[16];
    float *src = (float *)(this + 0x34); // this is int*, offset in int units
    for (int i = 0; i < 16; i++)
    {
        localMatrix[i] = src[i];
    }

    // Apply a transformation: presumably a rotation/scale using the given type and scaled factor
    // FUN_0046cf70(localMatrix, transformType, scaleFactor * g_globalScale, 1)
    applyMatrixTransform(localMatrix, transformType, scaleFactor * g_globalScale, 1);

    // Copy modified matrix back to object
    float *dst = (float *)(this + 0x34);
    for (int i = 0; i < 16; i++)
    {
        dst[i] = localMatrix[i];
    }

    // Zero out translation components (indices 3, 7, 11) – these are the tx, ty, tz in row-major
    dst[3]  = 0.0f; // (0,3)
    dst[7]  = 0.0f; // (1,3)
    dst[11] = 0.0f; // (2,3)

    // Set homogeneous w component (index 15) to a global value
    dst[15] = g_globalW; // DAT_00e2b1a4

    // Notify system of transform change (calls vfunc at +0x68)
    FUN_006101b0();  // likely some engine callback
    (**(code **)(*this + 0x68))(); // virtual method: onTransformUpdated?
}