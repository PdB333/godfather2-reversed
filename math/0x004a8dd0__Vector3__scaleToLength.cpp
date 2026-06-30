// FUNC_NAME: Vector3::scaleToLength
// Address: 0x004a8dd0
// Scales a vector to a specific length (global constant). 
// Input vector passed via EAX, output written to pointer in EDX.
// Uses threshold to avoid zero-length vectors.

#include <cmath> // for SQRT, though in game likely intrinsic

// Global constants – named based on usage
extern float kLengthEpsilonSq;   // = DAT_00e2cbe0
extern float kDesiredLength;     // = DAT_00e2b1a4

void __fastcall scaleVectorToLength(const float* inVec, float* outVec)
{
    float lenSq = inVec[0] * inVec[0] + inVec[1] * inVec[1] + inVec[2] * inVec[2];

    float scale;
    if (lenSq <= kLengthEpsilonSq) {
        scale = 0.0f;
    } else {
        scale = kDesiredLength / std::sqrt(lenSq);
    }

    outVec[0] = inVec[0] * scale;
    outVec[1] = inVec[1] * scale;
    outVec[2] = inVec[2] * scale;
}