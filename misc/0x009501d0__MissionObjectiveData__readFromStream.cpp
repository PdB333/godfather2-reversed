// FUNC_NAME: MissionObjectiveData::readFromStream

void __thiscall MissionObjectiveData::readFromStream(int thisPtr, undefined4 streamHandle)
{
    char isEnd;
    undefined4 readValue;
    int tokenPtr;
    undefined4 *quatPtr;
    undefined1 localBuffer[12];
    undefined4 local_b4;
    undefined4 local_a4;
    undefined4 local_94;
    undefined8 local_90;
    undefined4 local_88;
    undefined4 local_84;
    
    beginReadChunk(streamHandle, 0xb390b11a);
    setReadMode(1);
    localBuffer[0] = 0;
    local_b4 = 0;
    local_a4 = 0;
    local_94 = 0;
    local_84 = _DAT_00d5780c;  // global stream context
    initStreamReader(localBuffer);
    advanceStream(localBuffer);
    
    // Store initial timestamp/sequence from local buffer
    *(undefined8 *)(thisPtr + 0x158) = local_90;
    *(undefined4 *)(thisPtr + 0x160) = local_88;
    
    beginReadChunk(streamHandle, 0xf4636937);
    isEnd = isEndOfStream();
    while (isEnd == '\0') {
        advanceStream();
        readValue = readInt32();
        switch(readValue) {
        case 0:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0x54) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 1:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0x58) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 2:
            advanceStream();
            readValue = readString();
            assignString(thisPtr + 0x5c, readValue);
            break;
        case 3:
            advanceStream();
            readValue = readString();
            assignString(thisPtr + 100, readValue);
            break;
        case 4:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0x6c) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 5:
            advanceStream();
            readValue = readString();
            assignStringWithMax(thisPtr + 0x70, readValue, 0x40, 0);
            break;
        case 6:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0xb0) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 7:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0xb4) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 8:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0xb8) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 9:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0xbc) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 10:
            advanceStream();
            readValue = readString();
            assignStringWithMax(thisPtr + 0xc0, readValue, 0x40, 0);
            break;
        case 11:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0x100) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 12:
            advanceStream();
            readValue = readString();
            assignStringWithMax(thisPtr + 0x104, readValue, 0x40, 0);
            break;
        case 13:
            advanceStream();
            quatPtr = (undefined4 *)readQuaternion();
            *(undefined4 *)(thisPtr + 0x144) = *quatPtr;
            *(undefined4 *)(thisPtr + 0x148) = quatPtr[1];
            *(undefined4 *)(thisPtr + 0x14c) = quatPtr[2];
            *(undefined4 *)(thisPtr + 0x150) = quatPtr[3];
            break;
        case 14:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0x154) = *(undefined4 *)(tokenPtr + 8);
            break;
        case 15:
            tokenPtr = advanceStream();
            *(undefined4 *)(thisPtr + 0x164) = *(undefined4 *)(tokenPtr + 8);
            break;
        }
        nextToken();
        isEnd = isEndOfStream();
    }
    return;
}