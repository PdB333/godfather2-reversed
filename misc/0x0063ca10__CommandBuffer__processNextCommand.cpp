// FUNC_NAME: CommandBuffer::processNextCommand
int CommandBuffer::processNextCommand(int index) // index passed in EAX, this in unaff_EDI
{
    int* currentPtr;
    int* basePtr;
    int cmdType;
    int result;

    if (index < 1) {
        currentPtr = (int*)getCurrentCommand(); // FUN_00625430
    } else {
        // Calculate pointer: base at +0xc, each entry 8 bytes (int + int)
        currentPtr = (int*)(*(int*)(this + 0xc) - 8 + index * 8);
        if (currentPtr < *(int**)(this + 0x8)) {
            goto processCommand;
        }
    }

    advanceCommand(); // FUN_00625ca0
    goto end;

processCommand:
    if (currentPtr != nullptr && *currentPtr != -1) {
        cmdType = *currentPtr;
        if (cmdType == 7) {
            if (canProcessCommand() == 0) { // FUN_00625f80
                advanceCommand(); // FUN_00625ca0
            } else {
                executeCommand(); // FUN_00625e70
                // Check if previous command type (4 or 3) exists and update pointer
                basePtr = (int*)(*(int*)(this + 0x8) - 8);
                if (basePtr == nullptr || (*basePtr != 4 && *basePtr != 3)) {
                    *(int**)(this + 0x8) = basePtr;
                    advanceCommand(); // FUN_00625ca0
                }
            }
        } else if (cmdType == 5) {
            executeSpecialCommand(); // FUN_00625700
            executeCommand(); // FUN_00625e70
            basePtr = (int*)(*(int*)(this + 0x8) - 8);
            if (basePtr == nullptr || (*basePtr != 4 && *basePtr != 3)) {
                *(int**)(this + 0x8) = basePtr;
                advanceCommand(); // FUN_00625ca0
            } else {
                advanceCommand(); // FUN_00625ca0
                // Shift command entries down (remove current command and compact)
                undefined4* writePtr = *(undefined4**)(this + 0x8);
                undefined4* readPtr = writePtr;
                while (writePtr - 4 < readPtr) {
                    *writePtr = readPtr[-2];
                    writePtr[1] = readPtr[-1];
                    readPtr -= 2;
                }
                readPtr = *(undefined4**)(this + 0x8);
                writePtr[-4] = *readPtr;
                writePtr[-3] = readPtr[1];
                // Check buffer capacity
                if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
                    expandBuffer(); // FUN_00627360
                }
                defragmentBuffer(); // FUN_006343b0
                *(int*)(this + 0x8) = *(int*)(this + 0x8) - 8;
            }
        } else {
            advanceCommand(); // FUN_00625ca0
        }
    }

end:
    // After processing, get the current command pointer
    int* cmdPtr = *(int**)(this + 0x8);
    if ((int*)(cmdPtr - 2) == nullptr) { // -8 bytes as int* (2 ints)
        return 0;
    }
    if (*(cmdPtr - 2) == 4) { // Command type 4
        return *(cmdPtr - 1) + 0x10; // Data offset + 0x10 (pointer to object)
    }
    // For other types, validate via some check
    result = checkCommandValidity(); // FUN_00633990
    if (result == 0) {
        return 0;
    }
    // Check buffer capacity again
    if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
        expandBuffer(); // FUN_00627360
    }
    return *(cmdPtr - 1) + 0x10;
}