// FUNC_NAME: scalePointToScreen
// Function address: 0x00582db0
// Scales a 4-component input vector by reciprocals of scale factors, then sets W to a global constant.
// Used for transforming coordinates between different resolution spaces (e.g., UI atlas to screen).
// Global constant DAT_00e2b1a4 is likely the target screen width or reference resolution.

void __thiscall scalePointToScreen(float *outputVector, float *scaleFactors, float *inputVector)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;

    // Global constant (likely screen width/resolution)
    float globalConstant = DAT_00e2b1a4;

    // Precompute scaling factors for Y and Z
    fVar4 = globalConstant / scaleFactors[1];  // scale Y
    fVar5 = globalConstant / scaleFactors[2];  // scale Z

    // Input vector components
    fVar1 = inputVector[1];
    fVar2 = inputVector[2];
    fVar6 = inputVector[3] * globalConstant;   // W multiplied by global constant

    // Output X = inputX * (globalConstant / scaleX)
    outputVector[0] = inputVector[0] * (globalConstant / scaleFactors[0]);

    // Output Y, Z with precomputed scales
    outputVector[1] = fVar1 * fVar4;
    outputVector[2] = fVar2 * fVar5;

    // Output W: first set to scaled version, then overwritten with the global constant
    outputVector[3] = fVar6;
    outputVector[3] = globalConstant;   // final W becomes the global constant

    return;
}