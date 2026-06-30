// FUNC_NAME: EARS::Framework::BinaryObject::readFromStream
void __thiscall EARSObject::readFromStream(int this, void* stream) {
    char isDone;
    int opcode;
    int value;
    int blockPtr;

    // Initialize the stream and verify magic number
    streamInit(stream);
    streamSetMagic(stream, 0x1db6c9d8);

    // Loop reading opcode blocks until stream ends
    isDone = streamIsEnd(stream);
    while (isDone == '\0') {
        streamAdvance(stream); // Move to next block
        opcode = streamReadOpcode(stream);
        switch(opcode) {
        case 0: // Set property at +0x50
            streamAdvance(stream);
            value = streamReadUint32(stream);
            setPropertyAt0x50(this + 0x50, value);
            break;
        case 1: // Read a sub-block into +0x58 buffer
            blockPtr = this + 0x58;
            streamAdvance(blockPtr);
            streamReadBlock(blockPtr);
            break;
        case 2: // Set property at offset 200 (+0xC8)
            blockPtr = streamAdvance(stream);
            *(int*)(this + 200) = *(int*)(blockPtr + 8);
            break;
        case 3: // Release an object (no null check)
            streamAdvance(stream);
            value = streamReadUint32(stream);
            releaseObject(value);
            break;
        case 4: // Release an object (with null check)
            streamAdvance(stream);
            value = streamReadUint32(stream);
            if (value != 0) {
                releaseObject(value);
            }
            break;
        case 5: // Same as case 4
            streamAdvance(stream);
            value = streamReadUint32(stream);
            if (value != 0) {
                releaseObject(value);
            }
            break;
        case 6: // Same as case 4
            streamAdvance(stream);
            value = streamReadUint32(stream);
            if (value != 0) {
                releaseObject(value);
            }
            break;
        case 7: // Same as case 4
            streamAdvance(stream);
            value = streamReadUint32(stream);
            if (value != 0) {
                releaseObject(value);
            }
            break;
        case 8: // Same as case 4
            streamAdvance(stream);
            value = streamReadUint32(stream);
            if (value != 0) {
                releaseObject(value);
            }
            break;
        case 9: // Set property at offset 0xCC
            blockPtr = streamAdvance(stream);
            *(int*)(this + 0xCC) = *(int*)(blockPtr + 8);
            break;
        }
        streamEndBlock(stream);
        isDone = streamIsEnd(stream);
    }
    return;
}