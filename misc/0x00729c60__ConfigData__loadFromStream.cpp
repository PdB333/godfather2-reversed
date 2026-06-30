// FUNC_NAME: ConfigData::loadFromStream
void __thiscall ConfigData::loadFromStream(void *this, Parser *parser)
{
    char isDone;
    int *valuePtr;
    int type;
    int *arrayPtr;

    // Initialize the parser and expect a specific hash (possibly identifying the data section)
    Parser::init(parser);
    Parser::expectHash(parser, 0xfd648a11);

    // Loop until the parser indicates no more data
    isDone = Parser::isDone(parser);
    while (isDone == '\0') {
        // Read the next typed value from the stream
        valuePtr = (int *)Parser::readValuePointer(parser);
        type = Parser::getNextType(parser);
        switch (type) {
        case 0:
            // Store into member array at offset 0x50
            *(int *)((char *)this + 0x50) = *(int *)((char *)valuePtr + 8);
            break;
        case 1:
            // Store into offset 0x54
            *(int *)((char *)this + 0x54) = *(int *)((char *)valuePtr + 8);
            break;
        case 2:
            // Offset 0x58
            *(int *)((char *)this + 0x58) = *(int *)((char *)valuePtr + 8);
            break;
        case 3:
            // Offset 0x5C
            *(int *)((char *)this + 0x5C) = *(int *)((char *)valuePtr + 8);
            break;
        case 4:
            // Offset 0x60
            *(int *)((char *)this + 0x60) = *(int *)((char *)valuePtr + 8);
            break;
        case 5:
            // Offset 0x64 (100 decimal)
            *(int *)((char *)this + 100) = *(int *)((char *)valuePtr + 8);
            break;
        case 6:
            // Offset 0x68
            *(int *)((char *)this + 0x68) = *(int *)((char *)valuePtr + 8);
            break;
        case 7:
            // Offset 0x6C
            *(int *)((char *)this + 0x6C) = *(int *)((char *)valuePtr + 8);
            break;
        case 8:
            // Offset 0x70
            *(int *)((char *)this + 0x70) = *(int *)((char *)valuePtr + 8);
            break;
        case 9:
            // Offset 0x74
            *(int *)((char *)this + 0x74) = *(int *)((char *)valuePtr + 8);
            break;
        }
        // Advance to the next element in the stream
        Parser::advance(parser);
        isDone = Parser::isDone(parser);
    }
    return;
}