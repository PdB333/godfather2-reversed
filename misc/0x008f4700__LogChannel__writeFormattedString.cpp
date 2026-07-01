// FUNC_NAME: LogChannel::writeFormattedString
void __thiscall LogChannel::writeFormattedString(int thisPtr, short *extraMessage, uint argCount, void **argArray)
{
    short currentChar;
    short *srcPtr;
    short *msgEnd;
    short *formatEnd;
    uint totalLen;
    int buffer;
    char *tempBuf;

    if (argCount == 0) {
        return;
    }

    // Check a debug / enabled flag in a base class at offset -0x2080 relative to this
    if ((*(uint *)(thisPtr - 0x2080) >> 0xb & 1) != 0) {
        // Logging disabled? Jump to a quick return (removed unreachable code)
        (**(code **)(**(int **)(thisPtr + 8) + 0x10))(2);
        return;
    }

    // Allocate a fixed-size buffer (0xF0 bytes) for temporary working space
    buffer = FUN_009c8e50(0xF0);
    if (buffer == 0) {
        tempBuf = 0;
    } else {
        tempBuf = FUN_00982280(0);
    }

    // Pointer to the format string stored in this object at offset +0x4E2 (wide string)
    short *formatString = (short *)(thisPtr + 0x4E2);
    if (*formatString == 0) {
        // No format string, just use the extra message directly
        FUN_004d4570(extraMessage);   // wide string copy
        FUN_00981eb0(&DAT_0120546e); // output to log with some device
    } else {
        // Determine length of extraMessage
        srcPtr = extraMessage;
        do {
            currentChar = *srcPtr;
            srcPtr = srcPtr + 1;
        } while (currentChar != 0);
        // Determine length of formatString
        formatEnd = formatString;
        do {
            currentChar = *formatEnd;
            formatEnd = formatEnd + 1;
        } while (currentChar != 0);

        // Calculate total required wide characters: extraMessage length + formatString length + 0x20 + 2
        totalLen = ((int)(formatEnd - (short *)(thisPtr + 0x4E4)) >> 1) + 0x20 +
                   ((int)(srcPtr - (short *)(extraMessage + 1)) >> 1);

        // Allocate a buffer for concatenated result
        int combinedBuffer = FUN_009c8e80(-(uint)((int)((ulonglong)totalLen * 2 >> 0x20) != 0) |
                                          (uint)((ulonglong)totalLen * 2));
        FUN_00b98205(combinedBuffer, totalLen, extraMessage, formatString); // wide string concatenation with length limit
        *(undefined2 *)(combinedBuffer + -2 + totalLen * 2) = 0; // null terminate

        // Copy concatenated string to temp buffer
        FUN_004d4570(combinedBuffer);
        FUN_00981eb0(&DAT_0120546e); // output to log
        FUN_00acc6d0(&DAT_00d5d584); // flush or update
        FUN_009c8f10(combinedBuffer); // free the combined buffer
    }

    // Process arguments: if argCount == 1, set a state flag; otherwise output each argument
    if (argCount == 1) {
        *(int *)(tempBuf + 0xC) = 3; // some state change
    } else {
        for (uint i = 0; i < argCount; i++) {
            FUN_004d4570(*(void **)(argArray + i)); // copy each argument (likely wide string)
            FUN_00981e70(&DAT_0120546e, 0, 0);       // output formatted?
        }
    }

    // Install a callback function for further output handling
    *(code **)(tempBuf + 0x14) = FUN_008f3920;

    // Finalize and flush
    FUN_00982e10();      // flush output
    FUN_0068c590(1);     // set logging level or enable?
}