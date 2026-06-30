// FUNC_NAME: Math::multiplyVec3Components
// Address: 0x0056b800
// Role: Performs component-wise multiplication of two 4-component vectors for the x,y,z components only,
//        leaving the w component of the destination unchanged. The destination pointer is passed in EAX,
//        the first source vector in EDX, and the second source vector on the stack (as third parameter).
//        The ECX register (first parameter) is unused.
// This is a non-standard __fastcall convention where the output pointer is in EAX.
// It is used for scaling the direction (xyz) of a homogeneous vector while preserving its w coordinate.

#include <cstdint>

void __fastcall multiplyVec3Components(
    uint32_t unusedECX,    // ECX, not used
    const float* inVec1,   // EDX, first input vector (x,y,z,w)
    const float* inVec2    // Stack, second input vector (x,y,z,w)
)
// Output: writes to float* in_EAX (passed in EAX register)
// Equivalent to: outVec->xyz = inVec1->xyz * inVec2->xyz; outVec->w = outVec->w (preserved)
{
    float v1x = inVec1[0];
    float v1y = inVec1[1];
    float v1z = inVec1[2];
    float v1w = inVec1[3];
    float v2x = inVec2[0];
    float v2y = inVec2[1];
    float v2z = inVec2[2];
    float v2w = inVec2[3];

    // The output pointer is in EAX; it is declared as a local pointer here for clarity.
    float* outVec;
    // In actual assembly, outVec is in EAX.
    // For reconstruction, we assume the caller has set EAX to point to the destination.
    // The following code is equivalent to the assembly:
    cpp:
    outVec[0] = v1x * v2x;   // x component
    outVec[1] = v1y * v2y;   // y component
    outVec[2] = v1z * v2z;   // z component
    // The original w is stored temporarily, then restored (i.e., preserved):
    float tempW = outVec[3];  // read original w (from prior value)
    outVec[3] = v1w * v2w;   // multiply w, then overwritten with original
    outVec[3] = tempW;        // restore original w

    return;
}