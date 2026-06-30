// FUNC_NAME: MathUtils::scaleFirstEightByGlobalOverField
// Address: 0x00515ef0
// Purpose: Scales the first 8 floats of a data array by (g_globalFactor / data[0x18]).
// The data pointer is passed in EAX (likely custom calling convention or a thunk).
// g_globalFactor is a global float constant (0x00e2b1a4).
// The function modifies data[0..7] in place. This is likely used to maintain
// a constraint on a matrix or vector set (e.g., orthonormality or determinant).
void MathUtils::scaleFirstEightByGlobalOverField(float* data)
{
    float scale = g_globalFactor / data[0x18]; // data[0x18] is offset 0x60 bytes from base
    data[0] *= scale;
    data[1] *= scale;
    data[2] *= scale;
    data[3] *= scale;
    data[4] *= scale;
    data[5] *= scale;
    data[6] *= scale;
    data[7] *= scale;
}