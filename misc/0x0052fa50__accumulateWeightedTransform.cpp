// FUNC_NAME: accumulateWeightedTransform
// Function at 0x0052fa50 applies a weighted blend to a 6-element transformation vector.
// The first 4 elements (likely quaternion/rotation) are scaled by a global weight and added,
// the last 2 elements (translation) are directly added.

void __fastcall accumulateWeightedTransform(float* outTransform, const float* inTransform)
{
    float weight = DAT_00e2b1a4; // Global weight factor

    // Accumulate rotation components (elements 0-3) with weight
    outTransform[0] += weight * inTransform[0];
    outTransform[1] += weight * inTransform[1];
    outTransform[2] += weight * inTransform[2];
    outTransform[3] += weight * inTransform[3];

    // Accumulate translation components (elements 4-5) directly
    outTransform[4] += inTransform[4];
    outTransform[5] += inTransform[5];
}