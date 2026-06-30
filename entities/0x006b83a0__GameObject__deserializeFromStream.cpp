// FUNC_NAME: GameObject::deserializeFromStream
void __thiscall GameObject::deserializeFromStream(void* thisPtr, void* streamHandle) {
    char isComplete;
    int opcode;
    int dataPtr;
    uint value;

    initStream(streamHandle);
    setChecksum(streamHandle, 0x6c8152cb);
    isComplete = isStreamComplete(streamHandle);
    while (isComplete == '\0') {
        skipPadding(streamHandle); // Possibly read alignment bytes
        opcode = readOpcode(streamHandle);
        switch(opcode) {
        case 0:
            skipPadding(streamHandle);
            value = readU32(streamHandle);
            setFieldAtOffset50(thisPtr, value); // +0x50
            break;
        case 1:
            dataPtr = readDataPointer(streamHandle);
            *(uint*)((char*)thisPtr + 0x58) = *(uint*)((char*)dataPtr + 8);
            break;
        case 2:
            dataPtr = readDataPointer(streamHandle);
            *(uint*)((char*)thisPtr + 0x5c) = *(uint*)((char*)dataPtr + 8);
            break;
        case 3:
            dataPtr = readDataPointer(streamHandle);
            *(uint*)((char*)thisPtr + 0x60) |= *(uint*)((char*)dataPtr + 8);
            break;
        case 4:
            dataPtr = readDataPointer(streamHandle);
            *(uint*)((char*)thisPtr + 100) = *(uint*)((char*)dataPtr + 8);
        }
        finishToken(streamHandle); // Move to next token
        isComplete = isStreamComplete(streamHandle);
    }
    return;
}