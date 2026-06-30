// FUNC_NAME: PathTokenizer::parseMarks
void PathTokenizer::parseMarks() {
    // +0x08: m_writePtr (current write position in token buffer)
    // +0x0c: m_readPtr (current read position)
    // +0x10: m_outputStream (pointer to output stream structure)
    // +0x14: m_bufferSizeTracker (pointer to size tracker, +4 is max size)
    // +0x18: m_bufferEnd (end of allocated buffer)
    // +0x1c: m_bufferStart (start of allocated buffer)
    // +0x20: m_bufferCapacity (number of 8-byte token slots)

    char* pathStr;
    int* headerPtr = *(int**)(this + 8); // pointer to header before string data

    if (headerPtr == nullptr) {
        pathStr = nullptr;
    } else if (*(int*)(headerPtr - 2) == 4) { // type field at offset -8 from headerPtr
        // +0x10 offset from data pointer at headerPtr[-1]
        pathStr = (char*)(*(int*)(headerPtr - 1) + 0x10);
    } else {
        int result = FUN_00633990(); // likely isStringType()
        if (result == 0) {
            pathStr = nullptr;
        } else {
            pathStr = (char*)(*(int*)(headerPtr - 1) + 0x10);
        }
        // Check if output stream needs flushing
        if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
            FUN_00627360(); // flush output stream
        }
    }

    pathStr = _strchr(pathStr, '?'); // find first '?' separator

    while (true) {
        if (pathStr == nullptr) {
            FUN_00625ca0(); // finalize tokenization
            FUN_00626460(); // cleanup
            return;
        }

        // Check for too many marks (overflow)
        int numMarks = (*(int*)(this + 8) - *(int*)(this + 0xc)) >> 3; // entries in buffer
        if (numMarks + 3 > 0x4000) {
            FUN_00627bd0("stack overflow (%s)", "too many marks in a path component");
            code* crash = (code*)swi(3);
            (*crash)();
            return;
        }

        // Ensure enough space in token buffer
        if (*(int*)(this + 0x18) - *(int*)(this + 8) < 0x19) { // less than 25 bytes left
            int oldCapacity = *(int*)(this + 0x20);
            int newCapacity = oldCapacity * 2;
            if (oldCapacity < 3) {
                newCapacity = oldCapacity + 0x17; // minimum capacity
            }
            int newSize = newCapacity * 8;
            int oldSize = oldCapacity * 8;
            int newBuffer = FUN_006279a0(oldSize, newSize); // reallocate buffer
            *(int*)(this + 0x18) = newBuffer - 0xa8 + newCapacity * 8; // new end pointer
            *(int*)(this + 0x1c) = newBuffer; // new start pointer
            *(int*)(this + 0x20) = newCapacity;
            FUN_00635b50(); // copy old data to new buffer
        }

        // Update size tracker
        uint newWritePos = *(int*)(this + 8) + 0x18;
        if (*(uint*)(*(int*)(this + 0x14) + 4) < newWritePos) {
            *(uint*)(*(int*)(this + 0x14) + 4) = newWritePos;
        }

        // Flush output stream if needed
        if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
            uint uVar6 = FUN_00627290(); // get flush token
            FUN_00626f80(); // begin flush
            FUN_00626fd0(0); // flush with flag
            FUN_00626f80(); // end flush?
            FUN_00627010(uVar6); // write token
            FUN_006270e0(); // finalize flush
        }

        // Write token entry (type 4 and hash)
        int* writePtr = *(int**)(this + 8);
        *writePtr = 4; // token type
        uint tokenHash = FUN_00638920(); // hash current segment
        writePtr[1] = tokenHash;
        // Copy to read pointer (for later processing)
        int* readPtr = *(int**)(this + 0xc);
        *readPtr = *writePtr;
        readPtr[1] = writePtr[1];
        // Advance write pointer by 8 bytes
        *(int*)(this + 8) = *(int*)(this + 8) + 8;

        // Find next '?' separator
        pathStr = _strchr(pathStr + 1, '?');
    }
}