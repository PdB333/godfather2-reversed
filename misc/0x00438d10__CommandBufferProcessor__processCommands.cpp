// FUNC_NAME: CommandBufferProcessor::processCommands
int __thiscall CommandBufferProcessor::processCommands(void *this) {
    int resultPayload = 0;
    int someValue = 0; // local_18
    bool hasExtraInput = false;
    int extraOffset = 0; // iVar8

    // First command (input base)
    int *inputBase = *(int **)((int)this + 0xC);
    int *outputEnd = *(int **)((int)this + 0x8);
    int *cmdPtr = inputBase;

    if (cmdPtr < outputEnd && cmdPtr != nullptr) {
        int type = *cmdPtr;
        if (type == 3) {
            someValue = cmdPtr[1];
        } else if (type == 4) {
            // Validate type 4 command via external condition
            int local_14; // output of validation function
            if (FUN_00636850(&local_14) != 0) {
                // Temporarily create a fake command to extract data
                int tempCmd[2] = {3, local_14};
                someValue = tempCmd[1];
            }
        }
    }

    // Third command (at offset 0x10 from base)
    cmdPtr = (int *)((int)inputBase + 0x10);
    if (cmdPtr < outputEnd && cmdPtr != nullptr) {
        int type = *cmdPtr;
        if (type == 4) {
            extraOffset = cmdPtr[1] + 0x10;
        } else if (type == 3) {
            int extResult = FUN_00633990((int)this);
            if (extResult != 0) {
                extraOffset = cmdPtr[1] + 0x10;
            }
            // Check if internal buffer needs resetting
            int *bufferState = *(int **)((int)this + 0x10);
            if ((unsigned int)bufferState[8] <= (unsigned int)bufferState[9]) {
                FUN_00627360();
            }
        }
        hasExtraInput = true;
    }

    // Process first command again for final payload
    cmdPtr = inputBase;
    if (cmdPtr < outputEnd) {
        if (cmdPtr != nullptr) {
            int type = *cmdPtr;
            if (type != 4 && type != 3) {
                // Handle type 7 or 2
                if (cmdPtr >= outputEnd || cmdPtr == nullptr ||
                    (type = *cmdPtr, type != 7 && type != 2)) {
                    goto output;
                }
                if (cmdPtr < outputEnd && cmdPtr != nullptr) {
                    if (type == 2) {
                        resultPayload = cmdPtr[1];
                    } else if (type == 7) {
                        resultPayload = cmdPtr[1] + 0x10;
                    } else {
                        resultPayload = 0;
                    }
                } else {
                    resultPayload = 0;
                }
                if (hasExtraInput) {
                    int buf = FUN_004dafd0(extraOffset);
                    FUN_005e2230(buf);
                }
            } else {
                // Type 4 or 3
                if (cmdPtr < outputEnd && cmdPtr != nullptr && type != 4) {
                    FUN_00633990((int)this);
                    int *bufferState = *(int **)((int)this + 0x10);
                    if ((unsigned int)bufferState[8] <= (unsigned int)bufferState[9]) {
                        FUN_00627360();
                    }
                }
                resultPayload = FUN_00438bb0(someValue);
            }
        }
        if (resultPayload != 0) {
            FUN_005e1fd0();
        }
    }

output:
    // Write output command (type 2) to buffer
    int *outputCmd = *(int **)((int)this + 0x8);
    *outputCmd = 2;
    outputCmd[1] = resultPayload;
    *(int *)((int)this + 0x8) = (int)outputCmd + 8;
    return 1;
}