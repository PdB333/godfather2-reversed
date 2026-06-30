// FUNC_NAME: TransformComponent::applyRotationToVector
void __fastcall TransformComponent::applyRotationToVector(float* inputVec, int thisObj)
{
    float* transformedVec = (float*)(thisObj + 0x1d0);
    float* pW = (float*)(thisObj + 0x1dc);
    float x = inputVec[0];
    float y = inputVec[1];
    float z = inputVec[2];

    // Store the original input vector into object's field at +0x1d0
    transformedVec[0] = x;
    transformedVec[1] = y;
    transformedVec[2] = z;

    // Apply global rotation matrix (3x3) to the vector
    // Matrix elements (likely stored in global memory, column-major?)
    // g0 = _DAT_011f69f0, g1 = fRam011f6a04, g2 = fRam011f6a08
    // g3 = _DAT_011f6a00, g4 = _DAT_011f69f8, g5 = fRam011f69fc
    // g6 = _DAT_011f6a10, g7 = fRam011f6a14?, g8 = fRam011f6a1c?
    // Note: The multiplication pattern is: newX = y*g3 + x*g0 + z*g6  etc.
    // This suggests the matrix is either transposed or uses a different convention.
    float newX = y * _DAT_011f6a00 + x * _DAT_011f69f0 + z * _DAT_011f6a10;
    float newY = y * fRam011f6a04 + x * _DAT_011f69f8 + z * fRam011f6a14;
    float newZ = y * fRam011f6a08 + x * fRam011f69fc + z * fRam011f6a1c;
    float oldW = *pW;  // Preserve the original fourth component (e.g., w-coordinate)

    // Write transformed vector back to object's fields at +0x1d0
    transformedVec[0] = newX;
    transformedVec[1] = newY;
    transformedVec[2] = newZ;
    // Restore the w component (translation is not applied to direction vectors)
    *pW = oldW;

    // If this object is the active entity (player/camera), update additional systems
    if (DAT_012058e8 == thisObj) {
        // Calls at 0x0060ad20 with arguments: thisObj+0x14 (some ID), thisObj+0x1c0 (another vector?), transformedVec
        FUN_0060ad20(*(undefined4*)(thisObj + 0x14), *(undefined4*)(thisObj + 0x1c0), transformedVec);
    }
}