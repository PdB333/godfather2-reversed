// FUNC_NAME: AnimationBlendController::updateSmoothInterpolation
void __fastcall updateSmoothInterpolation(void* outputStruct, float* targetValues)
{
    float deltaTime;
    float value1, value2, value3, value4;
    float scaleFactor, temp, blendValue;

    // Check bit 7 of the integer representation of targetValues[5] (flags)
    // Equivalent to: if ((reinterpret_cast<uint32_t>(targetValues[5]) & (1 << 7)) == 0)
    if ((~(uint8_t)((uint32_t)targetValues[5] >> 7) & 1) != 0)
    {
        value1 = targetValues[2]; // e.g., target velocity or acceleration
        if (DAT_00e2b1a4 < value1)
        {
            // DAT_00e2b1a4 is a time step constant (likely dt)
            // Compute scaling factors for interpolation
            deltaTime = DAT_00e2b1a4;
            scaleFactor = deltaTime / (value1 - deltaTime);
            temp = targetValues[3] - deltaTime;   // targetValues[3] might be a max threshold
            blendValue = deltaTime / targetValues[4]; // targetValues[4] is a blend factor

            // Smooth interpolation of position/value fields in outputStruct
            float* outVal1 = (float*)((char*)outputStruct + 0x1c); // +0x1c
            float* outVal2 = (float*)((char*)outputStruct + 0x28); // +0x28

            float baseValue = targetValues[0];
            float newBase = baseValue * scaleFactor * temp;   // targetValues[0] updated
            *outVal2 += (targetValues[3] - value1) * blendValue; // adjust second output
            *outVal1 += (newBase - baseValue) * blendValue;   // adjust first output

            // Store updated values back
            targetValues[0] = newBase;                     // updated base
            targetValues[1] = scaleFactor * targetValues[1] * temp; // updated second value
        }
    }
}