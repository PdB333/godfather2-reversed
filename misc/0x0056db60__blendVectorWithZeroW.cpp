// FUNC_NAME: blendVectorWithZeroW
void __cdecl blendVectorWithZeroW(float t, int sourceA, int sourceB, int dest)
{
    // Call some initialization function with t, sources, dest, and a global constant.
    FUN_0056cc80(t, sourceA, sourceB, dest, DAT_00e2e780);

    // DAT_00e2b1a4 is likely 1.0f (or max blend factor)
    float oneMinusT = DAT_00e2b1a4 - t;

    // SourceA stores a 3D vector (or quaternion) at offset 0x10 (4 floats: x,y,z,w)
    // Compute scaled component from sourceA
    float v0 = *(float *)(sourceA + 0x10);
    float v1 = *(float *)(sourceA + 0x14);
    float v2 = *(float *)(sourceA + 0x18);
    float v3 = *(float *)(sourceA + 0x1c);

    float scaledX = oneMinusT * v0;
    float scaledY = oneMinusT * v1;
    float scaledZ = oneMinusT * v2;
    float scaledW = oneMinusT * v3;

    // Store partial result into destination (temporary)
    *(float *)(dest + 0x10) = scaledX;
    *(float *)(dest + 0x14) = scaledY;
    *(float *)(dest + 0x18) = scaledZ;
    *(float *)(dest + 0x1c) = scaledW;

    // Add scaled component from sourceB (weighted by t)
    float bX = *(float *)(sourceB + 0x10);
    float bY = *(float *)(sourceB + 0x14);
    float bZ = *(float *)(sourceB + 0x18);
    float bW = *(float *)(sourceB + 0x1c);

    *(float *)(dest + 0x10) = t * bX + scaledX;
    *(float *)(dest + 0x14) = t * bY + scaledY;
    *(float *)(dest + 0x18) = t * bZ + scaledZ;
    *(float *)(dest + 0x1c) = t * bW + scaledW;

    // Force the fourth component to 0 (likely w for directional vectors or homogeneous transform)
    *(undefined4 *)(dest + 0x1c) = 0;
}