// FUNC_NAME: NineFieldObject::deserializeProperties
void __thiscall NineFieldObject::deserializeProperties(int* this, void* stream)
{
    char isEnd;
    int fieldIndex;
    int fieldDataPtr;

    initializeStreamReader(stream, 0x9c61ae2c);
    isEnd = isStreamEnd(stream);
    while (isEnd == '\0') {
        readNextFieldPointer(stream); // advance to next field
        fieldIndex = getFieldIndex(stream);
        switch (fieldIndex) {
        case 0:
            fieldDataPtr = readNextFieldPointer(stream);
            this[0] = *(int*)(fieldDataPtr + 8); // +0x00
            break;
        case 1:
            fieldDataPtr = readNextFieldPointer(stream);
            this[1] = *(int*)(fieldDataPtr + 8); // +0x04
            break;
        case 2:
            fieldDataPtr = readNextFieldPointer(stream);
            this[2] = *(int*)(fieldDataPtr + 8); // +0x08
            break;
        case 3:
            fieldDataPtr = readNextFieldPointer(stream);
            this[3] = *(int*)(fieldDataPtr + 8); // +0x0C
            break;
        case 4:
            fieldDataPtr = readNextFieldPointer(stream);
            this[4] = *(int*)(fieldDataPtr + 8); // +0x10
            break;
        case 5:
            fieldDataPtr = readNextFieldPointer(stream);
            this[5] = *(int*)(fieldDataPtr + 8); // +0x14
            break;
        case 6:
            fieldDataPtr = readNextFieldPointer(stream);
            this[6] = *(int*)(fieldDataPtr + 8); // +0x18
            break;
        case 7:
            fieldDataPtr = readNextFieldPointer(stream);
            this[7] = *(int*)(fieldDataPtr + 8); // +0x1C
            break;
        case 8:
            fieldDataPtr = readNextFieldPointer(stream);
            this[8] = *(int*)(fieldDataPtr + 8); // +0x20
        }
        endFieldReading(stream);
        isEnd = isStreamEnd(stream);
    }
    return;
}