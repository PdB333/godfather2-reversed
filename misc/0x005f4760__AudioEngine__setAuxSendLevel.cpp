// FUNC_NAME: AudioEngine::setAuxSendLevel

bool __thiscall AudioEngine::setAuxSendLevel(int thisPtr, float soundGroupID, float sendLevel) {
    int index;
    int iVar1, iVar3, iVar4, iVar6, iVar7;
    float *pfVar8;
    unsigned int uVar5;
    float fVar2;
    bool result = false;

    // Search array at this+0x82ac (stride 0x5c) for a matching sound group
    index = 0;
    pfVar8 = (float *)(thisPtr + 0x82ac);
    while (pfVar8[1] < 0.0f || *pfVar8 != soundGroupID) {
        index++;
        pfVar8 += 0x5c / sizeof(float); // stride 0x5c = 23 floats
        if (index > 9) {
            return false;
        }
    }
    if (index < 0) {
        return false;
    }

    // Get the state structure at this+0x8210 + index*0x170
    iVar3 = index * 0x170 + 0x8210 + thisPtr;

    // Acquire audio mutex (assumed)
    FUN_00ab4db0(&DAT_00e2aea0);

    // Retrieve handle index from state field +0x9c, multiply by 0x10 to get offset into handle array
    iVar4 = *(int *)(iVar3 + 0x9c) * 0x10;
    iVar1 = *(int *)(iVar4 + 0x81c4 + thisPtr); // pointer to audio node

    if (iVar1 != 0) {
        // Get auxiliary send handles
        uVar5 = FUN_004dafd0("AuxSend3", &soundGroupID);
        iVar6 = FUN_005e9d90(uVar5, &soundGroupID); // some integer handle

        uVar5 = FUN_004dafd0("AuxSend1", &soundGroupID);
        iVar7 = FUN_005e9d90(uVar5, &soundGroupID);

        // Check if send level should be applied: threshold from global? (DAT_00e2b05c)
        if (DAT_00e2b05c <= *(float *)(iVar3 + 0x134) && iVar6 != 0) {
            // Update the volume (or parameter) for the state
            *(float *)(iVar3 + 0x98) = sendLevel;
            soundGroupID = *(float *)(iVar3 + 0x90) * sendLevel; // possibly attenuation factor

            // Begin audio parameter update
            FUN_00c9eac0(); // likely beginSetParameterBatch or similar

            if (iVar7 != 0) {
                fVar2 = soundGroupID;
                // Check a flag at this+0x9089 (e.g., mute?)
                if (*(char *)(thisPtr + 0x9089) == '\0') {
                    fVar2 = 0.0f;
                }
                // Set parameter for aux send 1 (index 0)
                FUN_00ca4e90(0, fVar2);
            }

            // Set parameter for aux send 3 (index 0)
            FUN_00ca4e90(0, soundGroupID);

            // End audio parameter update
            FUN_00c9eae0();

            result = true;
        }

        // Update the audio node (probably commit parameter changes)
        // Parameters: this, handle ID from +0x81c0, and the pointer to node
        FUN_005ebfa0(thisPtr, *(int *)(iVar4 + thisPtr + 0x81c0), iVar1);
    }

    // Release audio mutex
    FUN_00ab4e70();
    return result;
}