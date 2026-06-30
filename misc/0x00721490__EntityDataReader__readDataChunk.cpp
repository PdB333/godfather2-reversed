// FUNC_NAME: EntityDataReader::readDataChunk
void __thiscall EntityDataReader::readDataChunk(int this, int streamHandle)
{
    char isEnd;
    int type;
    int value;
    int *pTarget;

    // Initialize stream and set stream handle
    initStream(streamHandle);
    beginChunk(streamHandle, 0xb390b11a); // Begin reading header chunk
    setChunkVersion(1);
    isEnd = isEndOfChunk();

    if (isEnd == 0) {
        // Read header data: a 12-byte buffer (likely for some basic info)
        char headerBuf[12];
        local_114 = 0;  // Unused? but probably initializing
        local_104 = 0;
        local_f4 = 0;
        local_e4 = _DAT_00d5780c; // Global constant (e.g., default value)
        nextElement(headerBuf);   // Position to header element
        readDataIntoBuffer(headerBuf); // Read 12 bytes into buffer? (but buffer is local)
        // Store read values into object fields: 8 bytes at +0x94, 4 bytes at +0x9c
        *(uint64*)(this + 0x94) = *(uint64*)(headerBuf + 4);  // local_f0 is at headerBuf+4? Approx
        *(uint32*)(this + 0x9c) = *(uint32*)(headerBuf + 12); // local_e8
    }

    // Now begin reading the next chunk
    beginChunk(streamHandle, 0xd081ffa2); // Begin reading body chunk
    isEnd = isEndOfChunk();

    while (isEnd == 0) {
        nextElement(); // Advance to next element
        type = getChunkType(); // Get type code (0-3)

        switch (type) {
        case 0:
            // Type 0: read an integer value and store at offset +0x6c
            nextElement();
            value = readChunkValue(); // Read value (e.g., int)
            setFieldAt(this + 0x6c, value); // Store at +0x6c
            break;

        case 1:
            // Type 1: read a data block into object at offset +0x84 (likely a vector or transform)
            pTarget = (int*)(this + 0x84);
            nextElement(pTarget);
            readVector(pTarget); // Reads multiple values (e.g., 3 floats)
            break;

        case 2:
            // Type 2: similar, at offset +0x74
            pTarget = (int*)(this + 0x74);
            nextElement(pTarget);
            readVector(pTarget);
            break;

        case 3:
            // Type 3: read flag data and OR it into a flags field at offset +0x50
            pTarget = (int*)nextElement(); // Get pointer to element data
            *(uint*)(this + 0x50) |= *(uint*)(pTarget + 8); // OR with the value at +8 in element
            break;
        }

        advanceChunk(); // Move to next chunk element
        isEnd = isEndOfChunk();
    }

    return;
}