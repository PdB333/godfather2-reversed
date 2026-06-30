// FUNC_NAME: accumulateWeightedVector
void accumulateWeightedVector(const float* inputVector)
{
    // Global accumulator for weighted sum of 4-component vector
    // Addresses from Ghidra:
    extern float gWeightedAccumX;   // 0x01125230
    extern float gWeightedAccumY;   // 0x01125234
    extern float gWeightedAccumZ;   // 0x01125238
    extern float gWeightedAccumW;   // 0x0112523c
    extern float gTotalWeight;      // 0x01125240
    const float kWeightFactor = (float&)0x00e2b1a4; // constant weight factor

    gWeightedAccumX += kWeightFactor * inputVector[0];
    gWeightedAccumY += kWeightFactor * inputVector[1];
    gWeightedAccumZ += kWeightFactor * inputVector[2];
    gWeightedAccumW += kWeightFactor * inputVector[3];
    gTotalWeight += kWeightFactor;
}