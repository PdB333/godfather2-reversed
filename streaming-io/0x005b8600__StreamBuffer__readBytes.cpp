// FUNC_NAME: StreamBuffer::readBytes
// Function at 0x005b8600
// Copies bytes from a source pointer to a destination pointer, advances the read pointer, and zeros consumed region in buffer.
// Structure assumed: [0x00] readPtr (pointer to current read position), [0x08] endPtr (pointer to end of buffer)
// Parameters: this (read state), param_2 (output destination pointer), param_3 (input source pointer)
// Returns: original destination pointer

undefined1* __thiscall StreamBuffer::readBytes(int* thisPtr, int** destOut, int** srcIn) {
    int savedEnd;           // iVar1, saved end pointer
    undefined1* destStart;  // puVar2, start of destination buffer
    int readPtr;            // iVar3, original read pointer
    undefined1* destWrite;  // puVar5, current destination write position
    undefined1* srcRead;    // puVar4, current source read position

    savedEnd = thisPtr[2];            // get end pointer (offset +0x08)
    destStart = (undefined1*)*destOut; // dereference to get actual destination start
    readPtr = thisPtr[0];              // get current read pointer (offset +0x00)
    destWrite = destStart;

    // Copy bytes from source to destination until source reaches (readPtr + endPtr)
    for (srcRead = (undefined1*)*srcIn; srcRead != (undefined1*)(readPtr + savedEnd); srcRead++) {
        *destWrite = *srcRead;
        destWrite++;
    }

    // Compute new offset value; if it wraps, zero the tail of buffer
    int newOffset = (*destOut - *srcIn) + thisPtr[0]; // destStart - srcStart + original readPtr
    if (newOffset < thisPtr[0]) {                     // wrapped around?
        do {
            *(undefined1*)(newOffset + thisPtr[2]) = 0; // zero byte at (newOffset + endPtr)
            newOffset++;
        } while (newOffset < thisPtr[0]);
    }

    // Advance read pointer by the number of bytes transferred
    thisPtr[0] = thisPtr[0] + (*destOut - *srcIn);    // add (destStart - srcStart)

    // Return original destination pointer
    return destStart + (thisPtr[2] - savedEnd);        // thisPtr[2] - savedEnd = 0, returns destStart
}