// FUNC_NAME: evaluateSteeringConstraint
// Function address: 0x006147c0
// Role: Checks steering/angle constraint for AI movement based on current direction and random factors.

#include <cstdint>

// External globals from game memory
extern float DAT_00e2b1a4;   // +/- 0x00e2b1a4: likely some angle threshold or scale
extern float DAT_00e2cd54;   // +/- 0x00e2cd54: another scale factor
extern float DAT_00e44564;   // +/- 0x00e44564: target direction component
extern float _DAT_011f6a30;  // +/- 0x011f6a30: some global reference vector component
extern float DAT_011f6af0[4]; // +/- 0x011f6af0: array of vectors or orientation (size 4 floats)

// Forward declaration of helper function (address 0x0056b480)
// Returns a direction vector and magnitude from global data and object index.
// This function likely fills outVec with 3 floats and returns a true magnitude.
void __fastcall getVehicleDirectionVector(unsigned int* dataArray, unsigned int objectIndex, float* outVec);

void __fastcall evaluateSteeringConstraint(unsigned int objectHandle, unsigned int randomSeed)
{
    float outVec[3];        // resulting direction vector
    float magnitude;        // scalar magnitude of the vector (stored on stack after outVec)

    // Call helper to get the current directional data for this object
    getVehicleDirectionVector(reinterpret_cast<unsigned int*>(&DAT_011f6af0), objectHandle, outVec);

    // magnitude is placed on stack at &outVec[3] by the helper
    magnitude = *(&outVec[3]);  // fStack_14

    // If magnitude is zero or negative, no constraint applied.
    if (magnitude <= 0.0f) {
        return;
    }

    // Extract lower 16 bits from random seed as a normalized random factor
    float randomFactor = static_cast<float>(randomSeed & 0xFFFF);

    // Compute the constraint equation:
    // (DAT_00e2b1a4 / magnitude) * outVec[0] + DAT_00e2b1a4) * randomFactor * DAT_00e2cd54
    //   + (DAT_00e44564 - _DAT_011f6a30) * randomFactor * DAT_00e2cd54 * (DAT_00e2b1a4 / magnitude) * in_XMM7_Da < 0.0

    // 'in_XMM7_Da' is a float passed via xmm7 (likely a cosine/sine angle parameter)
    float angleParam = in_XMM7_Da;  // retrieve from xmm7 register (assumed from calling context)

    float ratio = DAT_00e2b1a4 / magnitude;
    float term1 = (ratio * outVec[0] + DAT_00e2b1a4) * randomFactor * DAT_00e2cd54;
    float term2 = (DAT_00e44564 - _DAT_011f6a30) * randomFactor * DAT_00e2cd54 * ratio * angleParam;

    if (term1 + term2 < 0.0f) {
        return; // constraint violated, return early
    }

    // No return value; function exits silently if constraint passed.
    return;
}