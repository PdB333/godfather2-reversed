// FUNC_NAME: AudioManager::processEventList
uint __thiscall AudioManager::processEventList(undefined4 param_1, float *typeOut, int posOut1, int posOut2, float *posOut3, int scaleOut) 
{
    undefined4 *quatRet;
    float *tempPtr;
    float *outputScale;
    int slotIndex;
    undefined4 quat0, quat1, quat2, quat3;
    int idx;
    int currentType;
    uint count;
    int typeId;
    float *typePtr;
    float10 tempFloat;
    unkbyte10 extraout_ST0;
    float fScale, fScaleY, fScaleZ;
    float *typeOutCurrent;
    uint slotCount;
    undefined4 slotArray[4]; // local_30
    float globalScale[4]; // local_20, fStack_1c, fStack_18, fStack_14

    // Get the global manager's array of event objects (offset +0x10) and count (+0x14)
    int *eventArray;
    if (*(int*)(DAT_011307c4 + 0x14) == 0) {
        eventArray = 0;
    } else {
        eventArray = *(int**)(DAT_011307c4 + 0x10);
    }

    // Initialize slot array to zero
    count = 0;
    slotArray[0] = 0;
    slotArray[1] = 0;
    slotArray[2] = 0;
    slotArray[3] = 0;
    int lastType3 = 0;
    int tempSlot2 = 0;
    int tempSlot3 = 0;

    if (*(uint*)(DAT_011307c4 + 0x14) != 0) {
        do {
            int eventPtr = eventArray[count];
            lastType3 = tempSlot2;
            switch (*(int*)(eventPtr + 0x20)) { // type field at +0x20
                case 1: // ATTACK event?
                    slotArray[0] = eventPtr;
                    break;
                case 3:
                case 4:
                case 5: // MOVE events?
                    tempSlot3 = eventPtr;
                    if ((tempSlot2 != 0) && (lastType3 = tempSlot2, slotArray[3] == 0)) {
                        slotArray[3] = eventPtr;
                    }
                    break;
                case 7: // SPECIAL event?
                    slotArray[1] = eventPtr;
                    break;
            }
            count++;
            tempSlot2 = lastType3;
        } while (count < *(uint*)(DAT_011307c4 + 0x14));
        slotArray[2] = lastType3;
    }

    // Count how many slots are filled
    slotCount = (uint)(slotArray[0] != 0);
    if (slotArray[1] != 0) {
        slotCount = (slotArray[0] != 0) + 1;
    }
    if (slotArray[2] != 0) {
        slotCount++;
    }
    if (slotArray[3] != 0) {
        slotCount++;
    }

    uint processedCount = slotCount;
    if (processedCount != 0) {
        outputScale = (float*)(scaleOut + 0xc); // float array at scaleOut+0xc
        typeOutCurrent = typeOut;
        int posBase1 = posOut1 - (int)posOut3; // offset for first vector output
        int posBase2 = posOut2 - (int)posOut3; // offset for second vector output

        // Global scale factors (likely from data section)
        globalScale[0] = DAT_00d5eee4;
        globalScale[1] = DAT_00d5eee4;
        globalScale[2] = DAT_00d5eee4;
        globalScale[3] = DAT_00d5eee4;

        do {
            int currentEvent = *(int*)(&slotArray + (-(int)typeOut + (int)typeOutCurrent)); // weird indexing but effectively slotArray[typeOutCurrent - typeOut]
            // Actually, the address calculation: local_30 + (-(int)param_2 + (int)local_54) where local_54 increments. So it's reading from slotArray[loopIndex].
            // In the reconstructed loop, we'll just use slotArray directly.

            // Get quaternion from some shared resource (e.g., animation orientation)
            quatRet = (undefined4*)FUN_004aab20(); // returns 4 floats
            quat1 = quatRet[1];
            quat2 = quatRet[2];
            quat3 = quatRet[3];
            undefined4* posBaseAddr = (undefined4*)(posBase1 + (int)posOut3);
            *posBaseAddr = quatRet[0];
            posBaseAddr[1] = quat1;
            posBaseAddr[2] = quat2;
            posBaseAddr[3] = quat3;

            // Get a scale factor
            tempFloat = (float10)FUN_004aabf0();
            *(float*)((posOut1 - scaleOut) + (int)outputScale) = (float)tempFloat;

            // Apply global scale to the quaternion
            float* posVec = (float*)(posBase1 + (int)posOut3);
            float vx = posVec[1];
            float vy = posVec[2];
            float vz = posVec[3];
            float* scaledPos = (float*)(posBase1 + (int)posOut3);
            scaledPos[0] = posVec[0] * globalScale[0];
            scaledPos[1] = vx * globalScale[1];
            scaledPos[2] = vy * globalScale[2];
            scaledPos[3] = vz * globalScale[3];

            typeId = *(int*)(currentEvent + 0x20) - 1;
            switch (typeId) {
                case 0: // type 1
                    *typeOutCurrent = DAT_00d5eee4;
                    int source = FUN_004aaa50(); // get source transform?
                    float srcX = *(float*)(source + 0x24);
                    float srcY = *(float*)(source + 0x28);
                    float srcZ = *(float*)(source + 0x2c);
                    posOut3[0] = *(float*)(source + 0x20);
                    posOut3[1] = srcX;
                    posOut3[2] = srcY;
                    posOut3[3] = srcZ;
                    // Scale by global constant
                    float scaleFactor = DAT_00d5ccf8;
                    posOut3[0] *= scaleFactor;
                    posOut3[1] *= scaleFactor;
                    posOut3[2] *= scaleFactor;
                    posOut3[3] *= scaleFactor;
                    break;
                case 2: // type 3?
                case 3: // type 4?
                case 4: // type 5?
                    *typeOutCurrent = DAT_00e445ac;
                    int source2 = FUN_004aaa50();
                    undefined4 offs0 = *(undefined4*)(source2 + 0x34);
                    undefined4 offs1 = *(undefined4*)(source2 + 0x38);
                    undefined4 offs2 = *(undefined4*)(source2 + 0x3c);
                    undefined4* targetVec = (undefined4*)(posBase2 + (int)posOut3);
                    targetVec[0] = *(undefined4*)(source2 + 0x30);
                    targetVec[1] = offs0;
                    targetVec[2] = offs1;
                    targetVec[3] = offs2;
                    float var1 = (float)FUN_004aaa80();
                    outputScale[-3] = var1;
                    float var2 = (float)FUN_004aaae0();
                    outputScale[-2] = var2;
                    source2 = FUN_004aaa50();
                    float srcX2 = *(float*)(source2 + 0x24);
                    float srcY2 = *(float*)(source2 + 0x28);
                    float srcZ2 = *(float*)(source2 + 0x2c);
                    posOut3[0] = *(float*)(source2 + 0x20);
                    posOut3[1] = srcX2;
                    posOut3[2] = srcY2;
                    posOut3[3] = srcZ2;
                    if (*(int*)(currentEvent + 0x20) == 3) {
                        outputScale[-1] = DAT_00e44750;
                        outputScale[0] = DAT_00e44868;
                    } else {
                        float var3 = (float)FUN_004aaac0();
                        outputScale[-1] = var3;
                        // cosine of something
                        float cosVal = (float)fcos(extraout_ST0);
                        outputScale[0] = cosVal;
                    }
                    break;
                case 6: // type 7
                    *typeOutCurrent = DAT_00d5ddec;
                    break;
            }
            typeOutCurrent++;
            posOut3 += 4;
            outputScale += 4;
            slotCount--;
        } while (slotCount != 0);
    }
    return processedCount & 0xffffff00;
}