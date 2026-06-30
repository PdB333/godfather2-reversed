// FUNC_NAME: Entity::deserialize
void __thiscall Entity::deserialize(int this, void* stream)
{
    char isEnd;
    int chunkType;
    int objPtr;
    float tempFloat;
    char tempArray[12]; // 12-byte temporary object (e.g., Vector3)
    int tempInt0 = 0;
    int tempInt1 = 0;
    int tempInt2 = 0;
    int tempInt3 = _DAT_00d5780c; // global constant

    // Begin reading a chunk with ID 0x5bc925cf
    beginReadChunk(stream);
    readChunkID(stream, 0x5bc925cf);

    isEnd = isEndOfChunks();
    while (isEnd == '\0') {
        readNextChunk(); // advance to next chunk
        chunkType = getChunkType();
        switch (chunkType) {
        case 0: // integer field at +0x94
            objPtr = readObject();
            *(int*)(this + 0x94) = *(int*)(objPtr + 8);
            break;
        case 1: // sub-object at +0x84 (e.g., matrix or vector)
            objPtr = this + 0x84;
            readObject(objPtr);
            readVector(objPtr); // or readMatrix
            break;
        case 2: // sub-object at +0x54
            objPtr = this + 0x54;
            readObject(objPtr);
            readVector(objPtr);
            break;
        case 3: // float squared at +0xa4
            objPtr = readObject();
            tempFloat = *(float*)(objPtr + 8);
            *(float*)(this + 0xa4) = tempFloat * tempFloat;
            break;
        case 4: // float scaled by global at +0xa0
            objPtr = readObject();
            tempFloat = *(float*)(objPtr + 8);
            *(float*)(this + 0xa0) = tempFloat * DAT_00d5ef84;
            break;
        case 5: // byte at +0xa8
            objPtr = readObject();
            *(char*)(this + 0xa8) = *(char*)(objPtr + 8);
            break;
        }
        endChunk();
        isEnd = isEndOfChunks();
    }

    // Begin another chunk with ID 0xb390b11a
    readChunkID(stream, 0xb390b11a);
    beginChunk(1); // flag = 1

    isEnd = isEndOfChunks();
    if (isEnd == '\0') {
        // Initialize temporary object and call finalizer
        char* pTemp = tempArray;
        tempArray[0] = 0; // local_b4 = 0
        tempArray[4] = 0; // local_a4 = 0
        tempArray[8] = 0; // local_94 = 0
        *(int*)(tempArray + 12) = _DAT_00d5780c; // local_84
        readObject(pTemp);
        readSomething(pTemp);
        finalizeLoad(tempArray); // FUN_006e8fd0
    }
    return;
}