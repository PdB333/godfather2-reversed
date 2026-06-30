// FUNC_NAME: SomeDataObject::deserializeFromStream
// Function address: 0x006be5f0
// Role: Reads structured data from a binary stream and populates object fields
// Offsets: +0x50 (int), +0x54 (int), +0x58 (String/ID), +0x60 (int?), +0x68 (int?)

void __thiscall SomeDataObject::deserializeFromStream(void* thisv, void* streamPtr) {
    char isDone;
    int chunkType;
    void* chunkData;

    // Initialize stream reader
    initStreamReader(streamPtr);
    // Check magic signature
    readStreamSignature(streamPtr, 0x34deb5cb);

    isDone = isStreamEnd(streamPtr);
    while (true) {
        if (isDone) {
            return;
        }
        // Read next chunk header
        chunkData = readNextChunk(streamPtr);
        chunkType = getChunkType(streamPtr);

        switch (chunkType) {
        case 0: // Field at +0x50 (int)
        {
            void* valPtr = readNextChunk(streamPtr);
            *(int*)((int)thisv + 0x50) = *(int*)((int)valPtr + 8);
            break;
        }
        case 1: // Field at +0x54 (int)
        {
            void* valPtr = readNextChunk(streamPtr);
            *(int*)((int)thisv + 0x54) = *(int*)((int)valPtr + 8);
            break;
        }
        case 2: // Field at +0x58 (string or ID)
        {
            readNextChunk(streamPtr); // discard chunk header
            uint stringID = readStringOrID(streamPtr);
            setStringMember((int)thisv + 0x58, stringID);
            break;
        }
        case 3: // Field at +0x60 (int? via setIntMember)
        {
            readNextChunk(streamPtr);
            uint val = readStringOrID(streamPtr);
            int target = (int)thisv + 0x60;
            setIntMember(target, val);
            break;
        }
        case 4: // Field at +0x68 (int? via setIntMember)
        {
            readNextChunk(streamPtr);
            uint val = readStringOrID(streamPtr);
            int target = (int)thisv + 0x68;
            setIntMember(target, val);
            break;
        }
        }

        // Advance to next chunk
        advanceStream(streamPtr);
        isDone = isStreamEnd(streamPtr);
    }
}