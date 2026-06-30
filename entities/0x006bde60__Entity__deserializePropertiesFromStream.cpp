// FUNC_NAME: Entity::deserializePropertiesFromStream
void __thiscall Entity::deserializePropertiesFromStream(int this, StreamHandle stream)
{
    char hasMoreData;
    int typeCode;
    undefined4* quatPointer;
    undefined4 quatValue;

    initReadStream(stream);
    readTypeHash(stream, 0xd31f07cd);  // expected chunk signature

    hasMoreData = checkHasMoreData(stream);
    while (hasMoreData == '\0') {
        advanceReader(stream);
        typeCode = readTypeCode(stream);
        if (typeCode == 0) {
            advanceReader(stream);
            quatValue = readSingleValue(stream);
            setFloatProperty(this + 0x80, quatValue);  // stores at offset +0x80
        }
        else if (typeCode == 1) {
            advanceReader(stream);
            quatPointer = (undefined4*)readVector4(stream);  // reads 4 consecutive values
            *(undefined4*)(this + 0x88) = *quatPointer;
            *(undefined4*)(this + 0x8c) = quatPointer[1];
            *(undefined4*)(this + 0x90) = quatPointer[2];
            *(undefined4*)(this + 0x94) = quatPointer[3];
        }
        endReadChunk(stream);
        hasMoreData = checkHasMoreData(stream);
    }
    return;
}