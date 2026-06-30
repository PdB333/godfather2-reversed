// FUNC_NAME: DefinitionReader::readNextRecord
// Address: 0x006da710
// Role: Reads one definition record from a binary/text stream, populating fields: a name string and 9 integer values.
// Fields offset: +0x54 (name[64]), +0x93 (null terminator), +0x94–+0xb0 (8 values), +0xb4 (1 value)

void __thiscall DefinitionReader::readNextRecord(int thisPtr, DataStream* stream)
{
    char isDone;
    int tokenType;
    char* sourceString;
    size_t copyCount;

    // Initialize parser and seek to expected object type (hash 0xfbde1e5c)
    stream->setupRead();
    stream->expectType(0xfbde1e5c);

    isDone = stream->isObjectFinished();
    while (!isDone) {
        stream->advanceToken();       // Move to next token in record
        tokenType = stream->getTokenType();

        switch (tokenType) {
        case 0:   // String: record name
            copyCount = 0x40;         // Max name length = 64 bytes
            stream->advanceToken();   // Probably redundant, but follows original
            sourceString = stream->getString();
            _strncpy((char*)(thisPtr + 0x54), sourceString, copyCount);
            *(char*)(thisPtr + 0x93) = '\0'; // Force null termination
            break;

        case 1:   // Integer value at offset 0xB4
            stream->advanceToken();
            *(int*)(thisPtr + 0xB4) = *(int*)(stream->getData() + 8);
            break;

        case 2:   // Value 0 at offset 0x94
            stream->advanceToken();
            *(int*)(thisPtr + 0x94) = *(int*)(stream->getData() + 8);
            break;

        case 3:   // Value 1 at offset 0x98
            stream->advanceToken();
            *(int*)(thisPtr + 0x98) = *(int*)(stream->getData() + 8);
            break;

        case 4:   // Value 2 at offset 0x9C
            stream->advanceToken();
            *(int*)(thisPtr + 0x9C) = *(int*)(stream->getData() + 8);
            break;

        case 5:   // Value 3 at offset 0xA0
            stream->advanceToken();
            *(int*)(thisPtr + 0xA0) = *(int*)(stream->getData() + 8);
            break;

        case 6:   // Value 4 at offset 0xA4
            stream->advanceToken();
            *(int*)(thisPtr + 0xA4) = *(int*)(stream->getData() + 8);
            break;

        case 7:   // Value 5 at offset 0xA8
            stream->advanceToken();
            *(int*)(thisPtr + 0xA8) = *(int*)(stream->getData() + 8);
            break;

        case 8:   // Value 6 at offset 0xAC
            stream->advanceToken();
            *(int*)(thisPtr + 0xAC) = *(int*)(stream->getData() + 8);
            break;

        case 9:   // Value 7 at offset 0xB0
            stream->advanceToken();
            *(int*)(thisPtr + 0xB0) = *(int*)(stream->getData() + 8);
            break;
        }

        stream->finalizeToken();   // Mark token as consumed
        isDone = stream->isObjectFinished();
    }
}