// FUNC_NAME: EARSPhysicsObject::applyTransform

void __thiscall EARSPhysicsObject::applyTransform(float *pNewVector, float scalar, uint32_t extraData)
{
    // +0x14: some handle/ID? used for debug rendering
    // +0x2d4: unknown
    // +0x2e0: current position/vector X (or quaternion x)
    // +0x2e4: Y component
    // +0x2e8: Z component
    // +0x2ec: W component (preserved)
    // +0x2f0: unknown (used for debug)
    // +0x300: velocity/acceleration X?
    // +0x304: velocity Y?
    // +0x308: velocity Z?
    // +0x30c: computed value (scaled sum of velocities)
    // +0x310: unknown (used for debug)
    // +0x314: extraData (stored)

    FUN_00414aa0(); // likely some pre-update check

    // Compute scaled velocity sum: (velX + velY + velZ) * scalar * globalFactor
    float *pVelocity = (float *)(this + 0x300);
    float velSum = pVelocity[0] + pVelocity[1] + pVelocity[2];
    *(float *)(this + 0x30c) = velSum * scalar * *DAT_00e44728;

    // Copy input vector into object's position (or quaternion)
    float *pPosition = (float *)(this + 0x2e0);
    pPosition[0] = pNewVector[0];
    pPosition[1] = pNewVector[1];
    pPosition[2] = pNewVector[2];

    // Apply global rotation matrix (3x3, stored at 0x011f69f0 row-major)
    // Matrix indices (row, col):
    // m00 = (float)_DAT_011f69f0   m01 = (float)fRam011f69f4   m02 = (float)_DAT_011f69f8
    // m10 = (float)fRam011f69fc   m11 = (float)_DAT_011f6a00   m12 = (float)fRam011f6a04
    // m20 = (float)_DAT_011f6a08   m21 = (float)fRam011f6a0c   m22 = (float)_DAT_011f6a10
    // Actually the code uses these globals in a specific order
    float x = pPosition[0];
    float y = pPosition[1];
    float z = pPosition[2];
    float newX = y * (float)fRam011f6a04 + x * (float)_DAT_011f69f0 + z * (float)_DAT_011f6a10;
    float newY = y * (float)_DAT_011f6a08 + x * (float)fRam011f69f4 + z * (float)fRam011f6a14;
    float newZ = y * (float)fRam011f6a0c + x * (float)_DAT_011f69f8 + z * (float)_DAT_011f6a18;
    // NOTE: The decompiled code has these multiplications and then assigns to the same fields.
    // The w component at +0x2ec is left unchanged.

    pPosition[0] = newX;
    pPosition[1] = newY;
    pPosition[2] = newZ;
    // W component preserved as-is

    // Store extra data
    *(uint32_t *)(this + 0x314) = extraData;

    // Debug rendering: if this object is the global selected one (DAT_012058e8)
    if (DAT_012058e8 == this) {
        // FUN_0060ad20 likely draws a debug marker at position
        FUN_0060ad20(*(uint32_t *)(this + 0x14), *(uint32_t *)(this + 0x2d4), pNewVector);
        // FUN_0060add0: draws velocity vector
        FUN_0060add0(*(uint32_t *)(this + 0x14), *(uint32_t *)(this + 0x2f0), (float *)(this + 0x300));
        // FUN_0060aa90: draws extra data label
        FUN_0060aa90(*(uint32_t *)(this + 0x14), *(uint32_t *)(this + 0x310), *(uint32_t *)(this + 0x314));
    }
}