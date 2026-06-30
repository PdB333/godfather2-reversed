// FUNC_NAME: AnimationDecoder::decompressAnimation
int __thiscall AnimationDecoder::decompressAnimation(AnimationDecoder *this) {
    bool needsWrap;
    int count1;
    char *byteStream;
    float *primaryOutput, *secondaryOutput, *tertiaryOutput;
    int signValue;
    float time, fractionalPart, wrapValue, temp;
    RandomState randomState; // local_c, assumed struct
    float constant1 = DAT_00e2b1a4; // 1.0f
    float threshold = DAT_00e2e780; // e.g., 0.5f

    // this->param_1[1] is a pointer to source data with type field
    int *sourceData = this->sourceData; // param_1[1]
    time = (float)this->inputTime; // param_1[2]

    // Determine which offset to use for random seed based on type (0-9 vs 10+)
    if ((sourceData->type & 0xff) < 10) { // offset 4
        randomState = *(undefined4 *)(sourceData + 0x24); // Actually this should be loading a seed
    } else {
        randomState = *(undefined4 *)(sourceData + 0x2c);
    }

    // Fractional part computation for time clamping
    float intPart = (float)(int)time;
    fractionalPart = time - intPart;
    float negFrac = constant1 - fractionalPart; // DAT_00e2b1a4 - fractionalPart

    if (threshold < fractionalPart) {
        if (threshold < negFrac) {
            needsWrap = true;
            wrapValue = negFrac;
        } else {
            time = (float)((int)time + 1);
            negFrac = 0.0f;
            fractionalPart = 0.0f;
            wrapValue = constant1;
            needsWrap = false;
        }
    } else {
        negFrac = 0.0f;
        fractionalPart = 0.0f;
        wrapValue = constant1;
        needsWrap = false;
        time = intPart;
    }

    // Allocate primary buffer if needed
    int *enginePtr = (int *)this->engine; // *param_1
    primaryOutput = (float *)enginePtr[0x38]; // +0x38
    int count1 = this->count1; // param_1[3]
    if (primaryOutput == 0) {
        primaryOutput = (float *)allocatePrimaryBuffer(count1); // FUN_0056ef10
        enginePtr[0x38] = (int)primaryOutput;
        constant1 = DAT_00e2b1a4;
    }

    // Determine byte stream source
    byteStream = (char *)(((int *)enginePtr[0x34])[0x14]); // engine+0x34+0x14
    signValue = *(int *)(sourceData + ((sourceData->type & 0xff) < 10 ? 0x20 : 0x28)); // signed int

    if (signValue < 0) {
        // Only primary output (8 floats per entry)
        temp = time;
        if (needsWrap) {
            for (int i = 0; i < count1; i++) {
                if (byteStream[i] == 0x02) {
                    temp = sampleRandomWrap(&randomState, temp); // FUN_0057d4e0
                    primaryOutput[0] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[1] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[2] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[3] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[4] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[5] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[6] = wrapValue;
                    primaryOutput[7] = constant1;
                } else if (byteStream[i] != 0) {
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    temp = advanceRandomState(&randomState);
                }
                primaryOutput += 8;
            }
        } else {
            for (int i = 0; i < count1; i++) {
                if (byteStream[i] == 0x02) {
                    temp = sampleRandomNoWrap(&randomState, temp); // FUN_0057dc70
                    primaryOutput[0] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[1] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[2] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[3] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[4] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[5] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[6] = wrapValue;
                    primaryOutput[7] = constant1;
                } else if (byteStream[i] != 0) {
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    temp = advanceRandomState(&randomState);
                }
                primaryOutput += 8;
            }
        }

        // Handle tertiary stream (count3)
        int count3 = this->count3; // param_1[5]
        if (count3 > 0) {
            int skipCount = this->count2 - this->count1; // param_1[4] - param_1[3]
            for (int i = 0; i < skipCount; i++) {
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                temp = advanceRandomState(&randomState);
            }
            tertiaryOutput = (float *)enginePtr[0x40]; // +0x40
            if (tertiaryOutput == 0) {
                tertiaryOutput = (float *)allocateTertiaryBuffer(count3); // FUN_00580b40
                temp = time;
                enginePtr[0x40] = (int)tertiaryOutput;
            }
            if (count3 > 0) {
                if (needsWrap) {
                    for (int i = 0; i < count3; i++) {
                        temp = sampleRandomWrap(&randomState, temp);
                        *tertiaryOutput = wrapValue;
                        tertiaryOutput++;
                    }
                } else {
                    for (int i = 0; i < count3; i++) {
                        temp = sampleRandomNoWrap(&randomState, temp);
                        *tertiaryOutput = wrapValue;
                        tertiaryOutput++;
                    }
                }
                return 1;
            }
        }
    } else {
        // Both primary and secondary output (8+4 floats per entry)
        // Allocate secondary buffer if needed
        secondaryOutput = (float *)enginePtr[0x3c]; // +0x3c
        if (secondaryOutput == 0) {
            secondaryOutput = (float *)allocateSecondaryBuffer(count1); // FUN_005807d0
            enginePtr[0x3c] = (int)secondaryOutput;
            constant1 = DAT_00e2b1a4;
        }
        temp = time;
        if (needsWrap) {
            for (int i = 0; i < count1; i++) {
                if (byteStream[i] == 0x02) {
                    temp = sampleRandomWrap(&randomState, temp);
                    *primaryOutput = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[1] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[2] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[3] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[4] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[5] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    primaryOutput[6] = wrapValue;
                    primaryOutput[7] = constant1;
                    // secondary
                    temp = sampleRandomWrap(&randomState, temp);
                    *secondaryOutput = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    secondaryOutput[1] = wrapValue;
                    temp = sampleRandomWrap(&randomState, temp);
                    secondaryOutput[2] = wrapValue;
                    secondaryOutput[3] = constant1;
                } else if (byteStream[i] != 0) {
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    temp = advanceRandomState(&randomState);
                }
                primaryOutput += 8;
                secondaryOutput += 4;
            }
        } else {
            for (int i = 0; i < count1; i++) {
                if (byteStream[i] == 0x02) {
                    temp = sampleRandomNoWrap(&randomState, temp);
                    *primaryOutput = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[1] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[2] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[3] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[4] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[5] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    primaryOutput[6] = wrapValue;
                    primaryOutput[7] = constant1;
                    // secondary
                    temp = sampleRandomNoWrap(&randomState, temp);
                    *secondaryOutput = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    secondaryOutput[1] = wrapValue;
                    temp = sampleRandomNoWrap(&randomState, temp);
                    secondaryOutput[2] = wrapValue;
                    secondaryOutput[3] = constant1;
                } else if (byteStream[i] != 0) {
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    advanceRandomState(&randomState);
                    temp = advanceRandomState(&randomState);
                }
                primaryOutput += 8;
                secondaryOutput += 4;
            }
        }

        // Handle tertiary stream
        int count3 = this->count3;
        if (count3 > 0) {
            int skipCount = this->count2 - this->count1;
            for (int i = 0; i < skipCount; i++) {
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                advanceRandomState(&randomState);
                temp = advanceRandomState(&randomState);
            }
            tertiaryOutput = (float *)enginePtr[0x40];
            if (tertiaryOutput == 0) {
                tertiaryOutput = (float *)allocateTertiaryBuffer(count3);
                temp = time;
                enginePtr[0x40] = (int)tertiaryOutput;
            }
            if (needsWrap) {
                for (int i = 0; i < count3; i++) {
                    temp = sampleRandomWrap(&randomState, temp);
                    *tertiaryOutput = wrapValue;
                    tertiaryOutput++;
                }
            } else {
                for (int i = 0; i < count3; i++) {
                    temp = sampleRandomNoWrap(&randomState, temp);
                    *tertiaryOutput = wrapValue;
                    tertiaryOutput++;
                }
            }
        }
    }
    return 1;
}