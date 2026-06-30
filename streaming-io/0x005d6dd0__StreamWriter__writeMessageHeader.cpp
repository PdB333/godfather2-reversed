// FUNC_NAME: StreamWriter::writeMessageHeader
static void writeMessageHeader() {
    // g_StreamManager is a global singleton pointer (DAT_01206880)
    // It has a write cursor pointer at offset +0x14.
    int* writeCursorPtr = (int*)(g_StreamManager + 0x14);  // pointer to current write position
    int* writePos = *writeCursorPtr;  // current write position (pointer into a buffer)

    // Write vtable pointer for the message type
    *(void**)writePos = (void*)&PTR_LAB_01126e88;  // probably a vtable or type descriptor
    writePos++;

    // Write 4 zero fields (e.g., unknown IDs or flags)
    writePos[0] = 0;  // field 1
    writePos[1] = 0;  // field 2
    writePos[2] = 0;  // field 3
    writePos[3] = 0;  // field 4

    // Write a global identifier (DAT_00e2b1a4 – likely an object type or message ID)
    writePos[4] = g_SomeIdentifier;

    // Advance cursor past the 5 written words (20 bytes)
    *writeCursorPtr = writePos + 5;
    writePos = *writeCursorPtr;

    // Write a count/length (0x3f = 63)
    *writePos = 0x3f;

    // Advance cursor past this word
    (*writeCursorPtr)++;
}