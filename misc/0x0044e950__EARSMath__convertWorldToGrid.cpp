// FUNC_NAME: EARSMath::convertWorldToGrid
// Function address: 0x0044e950
// Converts a 3D world coordinate (x, y?, z) to 2D grid integer coordinates using scale and offset.
// The object (this) contains: +0x0C: float m_scale, +0x10: int m_offsetX, +0x14: int m_offsetZ.
// Global constants for float-to-int rounding: DAT_00e44648, DAT_00e44564, DAT_00e2b1a4 (likely specific to EARS engine).

extern const unsigned int DAT_00e44648;  // e.g., 0x4B400000 (8388608.0f) for rounding
extern const unsigned int DAT_00e44564;  // e.g., 0x3F800000 (1.0f) ?
extern const unsigned int DAT_00e2b1a4;  // e.g., 0x00000001 (adjustment mask)

void __thiscall EARSMath::convertWorldToGrid(float* vecIn, int* outX, int* outZ)
{
    float scale = *(float*)(this + 0x0C);   // scaling factor
    float inX = vecIn[0];
    float inZ = vecIn[2];                    // use x and z (ignore y)

    // Convert input X to integer grid coordinate
    float scaledX = inX * scale;
    float rounderX = (float)(DAT_00e44648 | (DAT_00e44564 & (unsigned int)scaledX));
    float intPartX = (scaledX + rounderX) - rounderX;  // truncate to integer (float)

    // Correction for potential rounding error
    float fracCheckX = (float)(DAT_00e44564 & (unsigned int)scaledX);
    unsigned int correctionX = (unsigned int)(fracCheckX < intPartX - scaledX) & DAT_00e2b1a4;
    float finalX = intPartX - (float)(-(int)correctionX);  // adjust if fraction too small

    *outX = (int)finalX - *(int*)(this + 0x10);  // subtract X offset

    // Convert input Z similarly
    float scaledZ = inZ * scale;
    float rounderZ = (float)(DAT_00e44648 | (DAT_00e44564 & (unsigned int)scaledZ));
    float intPartZ = (scaledZ + rounderZ) - rounderZ;
    float fracCheckZ = (float)(DAT_00e44564 & (unsigned int)scaledZ);
    float correctionZ = (float)(-(unsigned int)(fracCheckZ < intPartZ - scaledZ) & DAT_00e2b1a4);
    float finalZ = intPartZ - correctionZ;

    *outZ = (int)finalZ - *(int*)(this + 0x14);  // subtract Z offset
}