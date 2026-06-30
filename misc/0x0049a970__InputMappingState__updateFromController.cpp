// FUNC_NAME: InputMappingState::updateFromController
void __thiscall InputMappingState::updateFromController(int thisPtr, int newControllerIndex)
{
    byte activeControllerIndex;
    int controllerSlotBase;
    undefined4 *controllerSlot;
    undefined4 *dest;
    undefined4 *src;
    int i;
    ControllerState localState; // size 0x44 = 68 bytes, but Ghidra misidentified as 16 bytes; assume actual struct
    int tempVar;
    int mappingListResult;
    undefined4 *mappingList;  // local_5c
    int mappingCount;         // local_58
    ushort inputMask1;        // local_40
    ushort inputMask2;        // uStack_3e
    ushort inputMask3;        // local_3c

    int oldIndex = *(int *)(thisPtr + 4);
    if (oldIndex != 0) {
        // Get the active controller index from global InputManager
        activeControllerIndex = *(byte *)(gInputManager + 0x565);
        if (activeControllerIndex == 0x11) {
            // No specific slot? Use the start of the controller array
            controllerSlot = (undefined4 *)(gInputManager + 0x2c);
        }
        else if (activeControllerIndex <= 0xf) {
            // Valid slot: base + 0x2c + index * 0x44 (each slot is 68 bytes)
            controllerSlot = (undefined4 *)(gInputManager + 0x2c + (uint)activeControllerIndex * 0x44);
        }
        else {
            goto skipProcessing;
        }

        if (controllerSlot != NULL) {
            // Copy controller slot data to local state (68 bytes / 17 dwords)
            src = controllerSlot;
            dest = (undefined4 *)&localState;
            for (i = 0x11; i != 0; i--) {
                *dest = *src;
                src++;
                dest++;
            }

            // Store the new controller index for later use?
            // This overwrites param_2? Actually local_60 = param_2, but not used further?
            // local_60 = param_2; // Not used? Possibly a bug or missing.

            // Clear the output bitfields in the controller slot
            *(ushort *)(controllerSlot + 4) = 0; // offset +4
            *(ushort *)((int)controllerSlot + 0x12) = 0; // offset +0x12
            *(ushort *)(controllerSlot + 5) = 0; // offset +5

            int loopIndex = 0;
            tempVar = oldIndex; // local_64
            do {
                // Call a function that returns a list of mapping indices
                // Signature: void getActiveMappings(undefined4 *resultStruct)
                // resultStruct likely contains mappingList and mappingCount
                getActiveMappings(&tempVar);

                if (mappingCount != 0) {
                    ushort bitForLoop = (ushort)(1 << (loopIndex & 0x1f));
                    undefined4 *iter = mappingList;
                    do {
                        ushort bitForElement = (ushort)(1 << (*(byte *)iter & 0x1f));
                        if ((inputMask1 & bitForLoop) != 0) {
                            *(ushort *)(controllerSlot + 4) |= bitForElement;
                        }
                        if ((inputMask2 & bitForLoop) != 0) {
                            *(ushort *)((int)controllerSlot + 0x12) |= bitForElement;
                        }
                        if ((inputMask3 & bitForLoop) != 0) {
                            *(ushort *)(controllerSlot + 5) |= bitForElement;
                        }
                        iter++;
                    } while (iter != mappingList + mappingCount);
                }
                if (mappingList != NULL) {
                    freeMappingList(mappingList);
                }
                loopIndex++;
            } while (loopIndex < 0x10);
        }
    }
skipProcessing:
    // Clear internal buffer at offset 0x190 (400) and store new index
    memset((void *)(thisPtr + 400), 0, 0x2b); // size 0x2b = 43 bytes
    *(int *)(thisPtr + 4) = newControllerIndex;
    return;
}