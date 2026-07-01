// FUNC_NAME: AudioChannel::updatePanWithRandomVariation
void __thiscall AudioChannel::updatePanWithRandomVariation(int thisPtr, float inputPan, int outputStruct) {
    char activeFlag;
    long double funcResult; // from virtual call
    float temp1, temp2, temp3, temp4, temp5, temp6;
    float absMask;
    float local_8;
    float local_c;
    int deadInt;

    local_8 = 0.0f;

    // Check if inputPan is valid (non-zero?)
    activeFlag = (char)isInputValid(inputPan); // FUN_0040fa60
    if (activeFlag == '\0') {
        // Input invalid -> use zero and output
        funcResult = 0.0;
        goto finalize;
    }

    inputPan = 0.0f;
    deadInt = 0;

    // Initialize some audio state (likely start of variation processing)
    initializeAudioState(0, &inputPan, &deadInt, 0, 0,
                         ZERO_FLOAT, ZERO_FLOAT, ZERO_FLOAT); // FUN_0079eab0
    applyLerpScale(&inputPan, ZERO_FLOAT); // FUN_00465400

    temp1 = MAX_PAN_VALUE; // _DAT_00d5780c

    // Check a flag from this+4 -> object[0xe0] + 0x10
    int* objPtr = *(int**)(thisPtr + 4);
    int* flagStruct = (int*)objPtr[0xe0];
    char flag = *(char*)(flagStruct + 0x10);
    if (flag == '\0') {
        inputPan = PAN_INVERT_CONST - inputPan; // e.g., 1.0 - inputPan
    }

    // Determine clamp bound
    if (inputPan < MIN_PAN_THRESHOLD) { // _DAT_00d577a0
        local_c = ZERO_FLOAT;
    } else {
        local_c = MAX_PAN_VALUE;
    }

    // Virtual function call: likely getChannelModulation() or getPanFactor()
    funcResult = (long double)(*(code**)(objPtr[0x1a8]))();

    // If virtual result is larger than a threshold, scale down
    if (PAN_SCALE_THRESHOLD < funcResult) {
        temp1 = (PAN_SCALE_THRESHOLD / (float)funcResult);
        temp1 = temp1 * temp1;
    }

    inputPan = temp1 * inputPan;

    // Compute abs-like operation (bitwise: absolute value on float bits)
    temp2 = inputPan;
    if (inputPan < 0.0f) {
        temp2 = PAN_INVERT_CONST - inputPan;
    }
    inputPan = temp2 * inputPan; // essentially square magnitude?

    // Clamp inputPan to [0, MAX_PAN_VALUE]
    temp2 = ZERO_FLOAT;
    if (inputPan <= ZERO_FLOAT) {
        // no change, temp2 = ZERO_FLOAT
    } else if (MAX_PAN_VALUE <= inputPan) {
        temp2 = MAX_PAN_VALUE;
    } else {
        temp2 = inputPan;
    }
    inputPan = temp2;

    // Get random value
    funcResult = (long double)getRandom(); // FUN_00549a20
    local_8 = (float)funcResult;

    // Choose side based on sign of virtual result (funcResult)
    if (0.0 <= (float)funcResult) {
        temp2 = MAX_PAN_VALUE;
    } else {
        temp2 = ZERO_FLOAT;
    }

    // Compare side with previously computed clamp bound
    if (temp2 == local_c) {
        // Bitwise absolute value on floats (mask with ABS_MASK = 0x7FFFFFFF)
        absMask = (float)((unsigned int)local_8 & ABS_MASK);
        float absRand2 = (float)((unsigned int)inputPan & ABS_MASK);
        if (absMask <= absRand2) {
            temp2 = 0.0f;
            temp3 = inputPan - local_8;
        } else {
            temp2 = local_8 - inputPan;
            temp3 = 0.0f;
        }
    } else {
        temp2 = 0.0f;
        temp3 = 0.0f;
    }

    // Compute a factor from object data + scaling constants
    float factor = *(float*)(*(int*)(objPtr[0x380] + 8)); // obj->someFloat
    temp4 = MAX_PAN_VALUE / (factor * PAN_FACTOR_SCALE); // DAT_00e44748
    temp5 = temp4 * DAT_012067e8 * PAN_VARIATION_A * temp1; // _DAT_00e540d4
    temp6 = temp4 * DAT_012067e8 * PAN_VARIATION_B * temp1; // _DAT_00e540d8

    temp1 = temp5;
    if (temp2 == local_c) {
        if (temp2 == 0.0f) {
            // branch with temp3
            if (temp3 != 0.0f) {
                temp1 = (float)((unsigned int)(inputPan - local_8) & ABS_MASK);
                if (temp6 <= temp1) {
                    // goto LAB_0085d1dd (already set)
                }
            }
        } else {
            temp6 = (float)((unsigned int)(inputPan - local_8) & ABS_MASK);
            if (temp6 < temp5) {
                temp1 = temp6;
            }
        }
    } else {
        // different branches with absolute values
        if ((float)((unsigned int)temp2 & ABS_MASK) < temp5) {
            temp1 = (float)((unsigned int)temp2 & ABS_MASK);
        }
        if (temp1 < temp5) {
            if (temp5 - temp1 <= temp6) {
                temp6 = temp5 - temp1;
            }
            if ((float)((unsigned int)temp3 & ABS_MASK) < temp6) {
                temp6 = (float)((unsigned int)temp3 & ABS_MASK);
            }
            temp6 = temp6 + temp1;
            temp1 = temp6;
        }
    }

    // Final computation
    temp1 = ZERO_FLOAT;
    if (MIN_PAN_THRESHOLD <= inputPan - local_8) {
        temp1 = MAX_PAN_VALUE;
    }
    local_8 = temp1 * temp1 + local_8; // Note: this might be intended as multiplication, but decompiler shows fVar3 * fVar5 + local_8

finalize:
    setRandomSeed(local_8); // FUN_00549a90
    *(float*)(outputStruct + 0xC) = local_8;
    return;
}