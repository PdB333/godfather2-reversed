// FUNC_NAME: MathUtils::normalizeVector
// Address: 0x00508e10
// Description: Normalizes a 3D vector to unit length. If the squared length is
//              below epsilon (DAT_00e2cbe0), the result is zero. The scaling
//              uses DAT_00e2b1a4 (likely 1.0f) as numerator.

#include <cmath>

static const float kNormalizeEpsilon = 0.0001f;  // approximate DAT_00e2cbe0

void __fastcall MathUtils::normalizeVector(const float* inVec, float* outVec)
{
    float lenSq = inVec[0] * inVec[0] +
                  inVec[1] * inVec[1] +
                  inVec[2] * inVec[2];

    float scale;
    if (lenSq <= kNormalizeEpsilon) {
        scale = 0.0f;
    } else {
        scale = 1.0f / sqrt(lenSq);
    }

    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}