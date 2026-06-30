// FUNC_NAME: StateMachine::updateTransition
// Function address: 0x0058b530
// This function appears to handle state transitions with blending/interpolation.
// It manages an array of floats (possibly state values or blend weights) and
// uses a callback to determine next state index.

int __thiscall StateMachine::updateTransition(
    int thisPointer,                    // param1: this pointer (contains state info at +0x7c)
    int object,                         // param2: some object with short arrays at offset +2, +4
    int* floatArrayDesc,                // param3: pointer to float array descriptor (ptr[0]=data ptr, ptr[1]=count)
    float param4,                       // param4: some time or value
    float param5,                       // param5: another time/value
    unsigned int flags,                 // param6: flags (bit0 used)
    int (*callback)(int,int,int*),      // param7: state transition callback
    unsigned int param8,                // param8: some mode (2 is special)
    int param9,                         // param9: additional data
    float param10                       // param10: some duration/rate
)
{
    short* indexArray = *(short**)(object + 4);  // short array at object+4, indices into float array
    short sVar1 = *indexArray;
    if ((unsigned int)floatArrayDesc[1] <= (unsigned int)(int)sVar1) {
        float local2c = 0.0f;
        errorHandler(&local2c);  // likely assertion or boundary fix
    }
    int firstIndex = (int)*(float*)(*floatArrayDesc + sVar1 * 4);  // read float, store as int (possibly truncated)
    sVar1 = indexArray[1];
    if ((unsigned int)floatArrayDesc[1] <= (unsigned int)(int)sVar1) {
        float local2c = 0.0f;
        errorHandler(&local2c);
    }
    int secondIndex = (int)*(float*)(*floatArrayDesc + sVar1 * 4);

    bool bVar9 = (flags & 2) == 2;  // flag bit1 check
    bool local40;

    // Determine if we should force transition based on param4/param5 comparison
    // If ((flags>>1 XOR flags) & 1) is 0, i.e., bit1==0 (flags even) then normal comparison
    // else if bit1 is set, reversed condition
    if (((flags >> 1 ^ flags) & 1) == 0) {
        if ((0.0f <= param5) || (param4 < 0.0f))
            local40 = false;
        else
            local40 = true;
        if (!(param4 < param5) && !local40)
            local40 = true;
        else
            local40 = false;
    } else {
        if (param5 < param4)
            local40 = true;
        else
            local40 = false;
    }

    bool updated = false;
    int newFirstIndex = firstIndex;

    // Condition to call callback: if firstIndex==-1 OR (bVar9) OR (param8<2 AND local40 != bVar9)
    if (((firstIndex == -1) || (bVar9)) || ((param8 < 2 && (local40 != bVar9)))) {
        int callbackResult = (*callback)(thisPointer, object, floatArrayDesc);
        if (firstIndex != callbackResult) {
            // Update float array indices with new values
            sVar1 = *indexArray;
            if ((unsigned int)floatArrayDesc[1] <= (unsigned int)(int)sVar1) {
                float local2c = 0.0f;
                errorHandler(&local2c);
            }
            *(float*)(*floatArrayDesc + sVar1 * 4) = (float)callbackResult;
            sVar1 = indexArray[1];
            if ((unsigned int)floatArrayDesc[1] <= (unsigned int)(int)sVar1) {
                float local2c = 0.0f;
                errorHandler(&local2c);
            }
            *(float*)(*floatArrayDesc + sVar1 * 4) = (float)firstIndex;
            sVar1 = indexArray[3];
            if ((unsigned int)floatArrayDesc[1] <= (unsigned int)(int)sVar1) {
                float local2c = 0.0f;
                errorHandler(&local2c);
            }
            *(float*)(*floatArrayDesc + sVar1 * 4) = param4;
            updated = true;
            newFirstIndex = callbackResult;
            secondIndex = firstIndex;
        }
    }

    if ((newFirstIndex < 0) || (*(char*)(object + 1) <= newFirstIndex)) {
        return 0;
    }

    int dataPtr = *(int*)(object + 0xc + newFirstIndex * 4);
    unsigned int uVal1 = (unsigned int)*(short*)(dataPtr + 2);
    if ((unsigned int)floatArrayDesc[1] <= uVal1) {
        float local2c = 0.0f;
        errorHandler(&local2c);
    }
    float currentVal = *(float*)(*floatArrayDesc + uVal1 * 4);

    unsigned int uVal2 = (unsigned int)*(short*)(object + 2);
    if ((unsigned int)floatArrayDesc[1] <= uVal2) {
        uVal1 = 0;
        errorHandler(&uVal1);
    }
    unsigned int someVal = *(unsigned int*)(*floatArrayDesc + uVal2 * 4);

    if (updated) {
        uVal2 = (uVal2 & 0xffffff00) | ((*(unsigned int*)(*(int*)(thisPointer + 0x7c) + 0x10) >> 5) & 0xff);
        char cVar4 = func_005918f0(thisPointer, dataPtr, floatArrayDesc, uVal2);
        float fVar12 = someGlobalFloat;  // DAT_00e2eff4
        if (cVar4 == 0) {
            if (bVar9) {
                // Push parameters for later function call
                float savedParam4 = param4;
                float savedParam5 = param5;
                unsigned int savedSomeVal = someVal;
                float savedCurrentVal = currentVal;
                int savedParam9 = param9;
                unsigned int savedFlags = flags;
                func_00581e90();  // some call that may modify stack
                param4 = savedParam4;
                param5 = savedParam5;
            }
        } else {
            *(int*)(*(int*)(thisPointer + 0x7c) + 0x1c) = 0;
            *(float*)(*(int*)(thisPointer + 0x7c) + 0x20) = fVar12;
            *(int*)(*(int*)(thisPointer + 0x7c) + 0x68) = dataPtr;
            param4 = 0.0f;
            param5 = fVar12;
            secondIndex = -1;
            float* pfVar6 = (float*)func_0058abc0(floatArrayDesc);
            *pfVar6 = someGlobalFloat;
        }
    }

    // Subsequent state update and possible transition blending
    unsigned int result = func_00590360(thisPointer, floatArrayDesc, param4, param5, flags, param9);

    // If param10 not equal to a specific sentinel and secondIndex valid and different from newFirstIndex
    if (((param10 != sentinelFloat) && (secondIndex >= 0)) && (secondIndex != newFirstIndex) && (secondIndex < *(char*)(object + 1))) {
        float* pfVar6 = (float*)func_0058abc0(floatArrayDesc);
        float fVar11 = *pfVar6;
        float currentTime = (float)func_00590360(thisPointer, floatArrayDesc, fVar11, fVar11, flags, param9);
        pfVar6 = (float*)func_0058abc0(floatArrayDesc);
        float fVar12 = *pfVar6;
        float someConst = someGlobalConst;  // DAT_00e2b1a4
        float fVar10 = currentVal;
        if ((currentVal < fVar12) && (currentVal - sentinel2 <= fVar11)) {
            fVar11 = fVar11 - (currentVal - sentinel2);
        }
        func_0058aca0(param4);
        float local30 = (fVar10 - fVar11) * (someConst / param10);
        if (local30 < 0.0f) {
            local30 = ((fVar12 + fVar10) - fVar11) * (someConst / param10);
        }
        if (someConst <= local30) {
            pfVar6 = (float*)func_0058abc0(floatArrayDesc);
            *pfVar6 = someGlobalFloat;
            local30 = someConst;
        }
        int uVar7 = func_005832d0(local30, flags);
        func_0056fb60();
        func_0056fb60();
        return uVar7;
    }

    return result;
}