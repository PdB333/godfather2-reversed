// FUNC_NAME: SomeClass::deserializeFromStream
void __thiscall SomeClass::deserializeFromStream(int thisPtr, StreamReader* stream)
{
    char isEnd;
    int propertyType;
    String strValue;
    float floatValue;
    Vector4* vector4Ptr;
    int objPtr;
    
    StreamReader::initialize(stream);
    StreamReader::setMagic(stream, 0xc1ae9ce7);
    isEnd = StreamReader::isStreamEnd(stream);
    while (isEnd == '\0') {
        StreamReader::readPropertyToken(stream);
        propertyType = StreamReader::readPropertyType(stream);
        switch(propertyType) {
        case 0:
            StreamReader::readPropertyToken(stream);
            strValue = StreamReader::readString(stream);
            this->setStringProperty(0x50, strValue);  // +0x50: string field
            break;
        case 1:
            StreamReader::readPropertyToken(stream);
            strValue = StreamReader::readString(stream);
            this->setStringProperty(0x58, strValue);  // +0x58: string field
            break;
        case 2:
            StreamReader::readPropertyToken(stream);
            vector4Ptr = StreamReader::readVector4(stream);
            *(float*)(thisPtr + 0x64) = vector4Ptr->x;  // +0x64: float4 start
            *(float*)(thisPtr + 0x68) = vector4Ptr->y;
            *(float*)(thisPtr + 0x6c) = vector4Ptr->z;
            *(float*)(thisPtr + 0x70) = vector4Ptr->w;
            break;
        case 3:
            objPtr = StreamReader::readPropertyToken(stream);
            *(int*)(thisPtr + 0x60) = *(int*)(objPtr + 8); // +0x60: some reference
            break;
        case 4:
            StreamReader::readPropertyToken(stream);
            strValue = StreamReader::readString(stream);
            floatValue = StreamReader::convertStringToFloat(strValue);
            *(float*)(thisPtr + 0x74) = floatValue; // +0x74: float
            break;
        case 5:
            StreamReader::readPropertyToken(stream);
            strValue = StreamReader::readString(stream);
            floatValue = StreamReader::convertStringToFloat(strValue);
            *(float*)(thisPtr + 0x78) = floatValue; // +0x78: float
            break;
        case 6:
            StreamReader::readPropertyToken(stream);
            strValue = StreamReader::readString(stream);
            floatValue = StreamReader::convertStringToFloat(strValue);
            *(float*)(thisPtr + 0x7c) = floatValue; // +0x7c: float
            break;
        case 7:
            objPtr = StreamReader::readPropertyToken(stream);
            *(int*)(thisPtr + 0x84) = *(int*)(objPtr + 8); // +0x84: reference
            break;
        case 8:
            StreamReader::readPropertyToken(stream);
            strValue = StreamReader::readString(stream);
            floatValue = StreamReader::convertStringToFloat(strValue);
            *(float*)(thisPtr + 0x80) = floatValue; // +0x80: float
            break;
        case 9:
            objPtr = StreamReader::readPropertyToken(stream);
            *(int*)(thisPtr + 0x88) = *(int*)(objPtr + 8); // +0x88: reference
            break;
        case 10:
            objPtr = StreamReader::readPropertyToken(stream);
            *(int*)(thisPtr + 0x8c) = *(int*)(objPtr + 8); // +0x8c: reference
            break;
        case 11:
            objPtr = StreamReader::readPropertyToken(stream);
            *(int*)(thisPtr + 0x90) = *(int*)(objPtr + 8); // +0x90: reference
            break;
        case 12:
            objPtr = StreamReader::readPropertyToken(stream);
            *(int*)(thisPtr + 0x94) = *(int*)(objPtr + 8); // +0x94: reference
            break;
        }
        StreamReader::advanceToNextProperty(stream);
        isEnd = StreamReader::isStreamEnd(stream);
    }
    return;
}