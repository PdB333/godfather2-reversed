// FUNC_NAME: CStateSoundManager::processObject
void __thiscall CStateSoundManager::processObject(int objectPtr)
{
    int parentObject;
    bool boolResult;
    int stateValue;
    int *containerPtr;
    float volume;
    int globalManager;
    int objectLocal;

    globalManager = DAT_01205228; // global audio/sound manager handle

    // +0x4: pointer to container? Subtract 0x48 to get parent object
    if (*(int *)(objectPtr + 4) == 0) {
        containerPtr = (int *)0x0;
    } else {
        containerPtr = (int *)(*(int *)(objectPtr + 4) + -0x48);
    }

    stateValue = *(int *)(objectPtr + 0x18); // +0x18: state enum

    // Check if state 6 and a mute flag (bit 4 of a dword at this+0x10+0x21b0) is set
    if ((stateValue == 6) && ((*(uint *)(*(int *)(this + 0x10) + 0x21b0) >> 4 & 1) != 0)) {
        return;
    }

    if (stateValue == 6) {
        boolResult = FUN_00717c70(); // isSoundChannelAvailable? or isMuted?
        if ((!boolResult) && (containerPtr != (int *)0x0)) {
            parentObject = FUN_0046a1f0(containerPtr, 0x38523fc3); // get audio resource by hash
            if (parentObject != 0) {
                volume = (float)(**(code **)(**(int **)(this + 0x10) + 0xbc))(parentObject); // get volume from audio resource
                if (volume != (float)0) {
                    FUN_00716860(globalManager, objectPtr, parentObject); // play sound with the resource
                }
            }
        }
    } else if (((stateValue != 7) && (stateValue - 0xc == 0)) && (containerPtr != (int *)0x0)) {
        // stateValue == 12
        objectLocal = 0; // set to 0 for the query
        boolResult = (**(code **)(*containerPtr + 0x10))(0x38523fc3, &objectLocal); // query container for audio resource
        if (boolResult == 0) {
            return;
        }
        if (globalManager == 0) {
            return;
        }
        volume = (float)(**(code **)(**(int **)(this + 0x10) + 0xbc))(globalManager); // get global volume
        if (volume == (float)0) {
            return;
        }
        FUN_00471610(); // some initialisation or count??
    }

    // common path
    FUN_00714330(objectPtr); // update object state or process
    *(int *)(this + 0x38) = globalManager; // store global manager at +0x38

    parentObject = FUN_007f41e0(); // get current time or frame
    if (parentObject != 0) {
        objectPtr = 2; // prepare argument
        FUN_004abc20(); // submit to audio system with arg 2
    }
    return;
}