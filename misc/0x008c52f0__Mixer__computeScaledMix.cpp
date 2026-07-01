// FUNC_NAME: Mixer::computeScaledMix
float __thiscall Mixer::computeScaledMix(uint mixFlags, int inputParamA, int inputParamB, int inputParamC, MixScaleArray* scaleArray)
{
    float accumulatedValue = 0.0f;

    // Check if mixFlags indicates channel A is active and internal flag at +0x1d0 is set
    if ((mixFlags & 3) != 0 && *(int*)(this + 0x1d0) != 0) {
        float valueA = sub_8c3730(inputParamA, inputParamB, scaleArray); // getMixValue
        accumulatedValue = valueA;
    }

    // If inputParamC is provided, accumulate its contribution
    if (inputParamC != 0) {
        float valueC = sub_8c3730(inputParamC, 0, scaleArray);
        accumulatedValue += valueC;
    }

    // Base volume/gain stored at +0x160
    float baseVolume = *(float*)(this + 0x160);

    // If scaleArray is valid and contains elements, apply baseVolume to each element
    if (scaleArray != nullptr && scaleArray->count != 0) {
        for (uint i = 0; i < scaleArray->count; i++) {
            scaleArray->data[i] = baseVolume * scaleArray->data[i];
        }
    }

    // Final result = baseVolume * accumulatedValue
    return baseVolume * accumulatedValue;
}