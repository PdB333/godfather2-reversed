// FUNC_NAME: CharacterModifier::applyModifier
void __thiscall CharacterModifier::applyModifier(int this, float *ioValue, int *context) {
    float factor = 0.0f;
    int *dataPtr = (int *)*context;
    if (dataPtr != nullptr) {
        int someFlag = *(int *)((int)dataPtr + 0x1ed8);  // +0x1ed8: some state/type indicator
        if (someFlag != 0 && someFlag != 0x48) {          // 0x48 = 72, likely a sentinel or invalid
            int *secondPtr = (int *)context[1];           // context[1] = secondary data pointer
            if (secondPtr != nullptr) {
                // FUN_008be840 returns a float10 (80-bit), convert to float
                factor = (float)FUN_008be840(*(undefined4 *)((int)secondPtr + 0x1ed4));
                // +0x1ed4: likely a time reference or animation progress value
            }
        }
    }
    // Linear interpolation between this->minValue (0x50) and this->maxValue (0x54)
    float minVal = *(float *)(this + 0x50);
    float maxVal = *(float *)(this + 0x54);
    float interpolated = (maxVal - minVal) * factor + minVal;
    *ioValue = *ioValue * interpolated;
}