// FUNC_NAME: quaternionMultiply
// Purpose: Multiply two quaternions (stored as float[4] with order x, y, z, w)
// Result: outResult = quatA * quatB (quaternion multiplication)
void __thiscall quaternionMultiply(float* outResult, float* quatA, float* quatB)
{
    float aX = quatA[0];
    float aY = quatA[1];
    float aZ = quatA[2];
    float aW = quatA[3];

    float bX = quatB[0];
    float bY = quatB[1];
    float bZ = quatB[2];
    float bW = quatB[3];

    // Compute product quaternion components: result = quatA * quatB
    // Formula: (w1*w2 - x1*x2 - y1*y2 - z1*z2, w1*x2 + x1*w2 + y1*z2 - z1*y2, ...)
    // But our storage is (x,y,z,w)
    // Here quatA = (aX, aY, aZ, aW), quatB = (bX, bY, bZ, bW)
    // Then quatA * quatB gives:
    // result.x = aW*bX + aX*bW + aY*bZ - aZ*bY
    // result.y = aW*bY - aX*bZ + aY*bW + aZ*bX
    // result.z = aW*bZ + aX*bY - aY*bX + aZ*bW
    // result.w = aW*bW - aX*bX - aY*bY - aZ*bZ

    outResult[0] = aX*bW + aW*bX + aY*bZ - aZ*bY;   // x component
    outResult[1] = aY*bW + aW*bY + aZ*bX - aX*bZ;   // y component
    outResult[2] = aZ*bW + aW*bZ + aX*bY - aY*bX;   // z component
    outResult[3] = aW*bW - aX*bX - aY*bY - aZ*bZ;   // w component

    // Note: The original code computed these with slightly different ordering,
    // but algebraically equivalent as shown above.
}