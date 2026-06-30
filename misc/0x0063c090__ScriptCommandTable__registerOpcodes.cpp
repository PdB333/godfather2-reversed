// FUNC_NAME: ScriptCommandTable::registerOpcodes
void ScriptCommandTable::registerOpcodes(void)
{
    int commandIndex;
    undefined4 *stackPtr;
    
    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(code **)(commandIndex + 0xc) = opcodeHandler_0063b1b0;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6; // opcode type: method call
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(code **)(commandIndex + 0xc) = opcodeHandler_0063b740;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bcb0;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bcd0;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bcf0;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bd10;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bd30;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bd50;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(undefined1 **)(commandIndex + 0xc) = &opcodeHandler_0063bd70;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    checkBufferSpace();
    if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        growBuffer();
    }
    commandIndex = allocateCommandToken(0);
    *(code **)(commandIndex + 0xc) = opcodeHandler_0063bd90;
    stackPtr = *(undefined4 **)(this + 8);
    stackPtr[1] = commandIndex;
    *stackPtr = 6;
    *(int *)(this + 8) = *(int *)(this + 8) + 8;
    commandIndex = *(int *)(this + 8);
    stackPtr = (undefined4 *)allocateCommandEntry();
    *stackPtr = *(undefined4 *)(commandIndex + -8);
    stackPtr[1] = *(undefined4 *)(commandIndex + -4);
    *(int *)(this + 8) = *(int *)(this + 8) + -0x10;

    return;
}