// FUNC_NAME: MathUtils::projectVectorOntoDirection
// Address: 0x004a0730
// Role: Projects sourceVector onto directionVector, storing result in outVector.
// Returns 1 if projection succeeded (direction vector has sufficient length), 0 otherwise.
// Uses bitwise masking on squared length to handle denormals/zero without branching.

#include <cstdint>

// Global constants (defined elsewhere in the binary)
extern float kProjectionEpsilon;       // DAT_00e44598 (small threshold for squared length)
extern uint32_t kSignMask;             // DAT_00e44680 (mask to clear sign bit, e.g., 0x7FFFFFFF)

int __cdecl projectVectorOntoDirection(float* outVector, float* sourceVector, float* directionVector)
{
    // Squared length of direction vector
    float sqLen = directionVector[0] * directionVector[0] +
                  directionVector[1] * directionVector[1] +
                  directionVector[2] * directionVector[2];

    // Interpret squared length as unsigned int, mask out sign bit, reinterpret as float,
    // then compare with epsilon threshold to avoid near-zero or denormal directions.
    // This is a common EA EARS engine trick for fast magnitude comparison.
    if (kProjectionEpsilon < *reinterpret_cast<float*>(&reinterpret_cast<uint32_t&>(sqLen) & kSignMask))
    {
        // Dot product of source and direction
        float dot = sourceVector[0] * directionVector[0] +
                    sourceVector[1] * directionVector[1] +
                    sourceVector[2] * directionVector[2];

        // Projection scalar = dot / squared length
        float scalar = dot / sqLen;

        // Store projected vector
        outVector[0] = directionVector[0] * scalar;
        outVector[1] = directionVector[1] * scalar;
        outVector[2] = directionVector[2] * scalar;
        return 1;
    }
    else
    {
        // Direction vector is too small, return zero vector
        outVector[0] = 0.0f;
        outVector[1] = 0.0f;
        outVector[2] = 0.0f;
        return 0;
    }
}