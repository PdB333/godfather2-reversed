// FUNC_NAME: ActionStateMachine::processCommands
void __thiscall ActionStateMachine::processCommands(void *this, void *commandList) {
    uint commandParam;
    bool hasMoreCommands;
    int commandType;
    int intValue;

    readCommands(commandList);
    initCommandState(commandList);
    resetFlags();

    // Notify or set signal (unused)
    setSignal(commandList, 0xc8c5d222);

    hasMoreCommands = hasMoreCommands();
    while (!hasMoreCommands) {
        nextCommand();
        commandType = getCommandType();
        switch (commandType) {
            case 0: { // Set object A
                nextCommand();
                intValue = getCommandValue();
                setObject((int *)&this[0x198], intValue);
                if (*(int *)&this[0x198] == 0) {
                    *(unsigned short *)&this[0x182] &= 0xfffe; // Clear flag 0
                } else {
                    *(unsigned short *)&this[0x182] |= 1;     // Set flag 0
                }
                break;
            }
            case 1: { // Set object C
                nextCommand();
                intValue = getCommandValue();
                setObject((int *)&this[0x1a8], intValue);
                if (*(int *)&this[0x1a8] == 0) {
                    *(unsigned short *)&this[0x182] &= 0xfffb; // Clear flag 2
                } else {
                    *(unsigned short *)&this[0x182] |= 4;     // Set flag 2
                }
                break;
            }
            case 2: { // Set object B
                nextCommand();
                intValue = getCommandValue();
                setObject((int *)&this[0x1a0], intValue);
                if (*(int *)&this[0x1a0] == 0) {
                    *(unsigned short *)&this[0x182] &= 0xfffd; // Clear flag 1
                } else {
                    *(unsigned short *)&this[0x182] |= 2;     // Set flag 1
                }
                break;
            }
            case 3: { // Set data pointer from command
                int *nextData = (int *)nextCommand();
                *(undefined4 *)&this[0x1b0] = nextData[2]; // +8 offset
                break;
            }
            case 4: { // Add to list A (offset 0x188)
                nextCommand();
                intValue = getCommandValue();
                addToList(this + 0x188, intValue);
                break;
            }
            case 5: { // Add to list B (offset 0x190)
                nextCommand();
                intValue = getCommandValue();
                addToList(this + 0x190, intValue);
                break;
            }
            case 6: { // Animation flags
                int *commandData = (int *)nextCommand();
                commandParam = commandData[2]; // +8 offset
                // Bit 1: set flag 0x2 in +0x180
                if (commandParam & 2) {
                    *(unsigned short *)&this[0x180] |= 2;
                }
                // Bit 2: either clear or set persistent animation handle
                if (commandParam & 4) {
                    // Persistent animation handle exists
                    *(unsigned short *)&this[0x180] |= 4;
                    if (*(int *)&this[0x1d0] == 0) {
                        int *alloc = (int *)allocateMemory(0x18);
                        if (alloc == 0) {
                            *(undefined4 *)&this[0x1d0] = 0;
                        } else {
                            *(undefined4 *)&this[0x1d0] = createAnimation();
                        }
                    }
                } else {
                    // Clear persistent
                    int handle = *(int *)&this[0x1d0];
                    *(unsigned short *)&this[0x180] &= 0xfffb; // Clear bit 2
                    if (handle != 0) {
                        updateAnimation();
                        updateAnimation();
                        deleteObject(handle);
                        *(undefined4 *)&this[0x1d0] = 0;
                    }
                }
                // Bit 3: set flag 0x8 in +0x180
                if (commandParam & 8) {
                    *(unsigned short *)&this[0x180] |= 8;
                } else {
                    *(unsigned short *)&this[0x180] &= 0xfff7;
                }
                // Bit 0: play/stop animation toggle
                if (commandParam & 1) {
                    playAnimation();
                } else {
                    stopAnimation();
                }
                break;
            }
        }
        advanceCommandIndex();
        hasMoreCommands = hasMoreCommands();
    }
}