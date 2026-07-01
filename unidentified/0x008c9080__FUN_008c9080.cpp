// FUNC_NAME: SomeClass::readFromArchive
// Function address: 0x008c9080
// Role: Deserializes object data from a binary archive stream (EARS serialization).
// Fields at offsets: +0x50 (int), +0x54 (String), +0x5c (String), +0x64 (String), +0x6c (int), +0x70-0x7c (Vector4)

void __thiscall SomeClass::readFromArchive(int thisPtr, int archive) {
    char hasMore;
    int tokenType;
    int readInt;
    int stringId;
    int* vectorPtr;

    // Begin reading archive with class ID 0x4f610139
    archiveBeginRead(archive);
    archiveSetClassId(archive, 0x4f610139);

    hasMore = archiveHasMoreData(archive);
    while (hasMore == 0) {
        archiveReadNextToken(archive);
        tokenType = archiveGetTokenType(archive);
        switch (tokenType) {
        case 0: // int field at +0x50
            readInt = archiveReadNextToken(archive);
            *(int*)(thisPtr + 0x50) = *(int*)(readInt + 8);
            break;
        case 1: // string field at +0x54
            archiveReadNextToken(archive);
            stringId = archiveReadStringId(archive);
            setStringAtOffset(thisPtr + 0x54, stringId);
            break;
        case 2: // string field at +0x5c
            archiveReadNextToken(archive);
            stringId = archiveReadStringId(archive);
            setStringAtOffset(thisPtr + 0x5c, stringId);
            break;
        case 3: // string field at +0x64
            archiveReadNextToken(archive);
            stringId = archiveReadStringId(archive);
            setStringAtOffset(thisPtr + 0x64, stringId);
            break;
        case 4: // int field at +0x6c
            readInt = archiveReadNextToken(archive);
            *(int*)(thisPtr + 0x6c) = *(int*)(readInt + 8);
            break;
        case 5: // Vector4 field at +0x70-0x7c
            archiveReadNextToken(archive);
            vectorPtr = (int*)archiveReadVector4(archive);
            *(int*)(thisPtr + 0x70) = vectorPtr[0];
            *(int*)(thisPtr + 0x74) = vectorPtr[1];
            *(int*)(thisPtr + 0x78) = vectorPtr[2];
            *(int*)(thisPtr + 0x7c) = vectorPtr[3];
        }
        archiveEndToken(archive);
        hasMore = archiveHasMoreData(archive);
    }
    return;
}