// FUNC_NAME: EntityData::loadFromStream
void __thiscall EntityData::loadFromStream(void* thisData, void* stream)
{
    char endFlag;
    int token;
    int readValue;

    streamInit(stream);
    streamSetTypeHash(stream, 0x500b9169);
    endFlag = streamIsEndOfStream(stream);
    while (endFlag == '\0') {
        streamAdvanceToken(stream);
        token = streamReadToken(stream);
        switch (token) {
        case 0:
            readValue = streamReadInt(stream);
            *(int32_t*)((int)thisData + 0x50) = *(int32_t*)(readValue + 8);
            break;
        case 1:
            readValue = streamReadInt(stream);
            *(int32_t*)((int)thisData + 0x54) = *(int32_t*)(readValue + 8);
            break;
        case 2:
            streamReadInt(stream);
            token = streamReadStringLength(stream);
            assignStringAt(thisData + 0x58, token);
            break;
        case 3:
            streamReadInt(stream);
            token = streamReadStringLength(stream);
            assignStringAt(thisData + 0x60, token);
            break;
        case 4:
            streamReadInt(stream);
            token = streamReadStringLength(stream);
            assignStringAt(thisData + 0x68, token);
            break;
        case 5:
            readValue = streamReadInt(stream);
            *(uint32_t*)((int)thisData + 0x70) |= *(uint32_t*)(readValue + 8);
        }
        streamEndToken(stream);
        endFlag = streamIsEndOfStream(stream);
    }
    if ((*(uint8_t*)((int)thisData + 0x70) & 1) != 0) {
        registerGlobalData(&DAT_0120e93c);
    }
    if ((*(uint32_t*)((int)thisData + 0x70) >> 1 & 1) != 0) {
        registerGlobalData(&DAT_0112a620);
    }
    return;
}