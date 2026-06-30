// FUNC_NAME: EntityState::readFromStream
void __thiscall EntityState::readFromStream(int thisPtr, Stream* stream)
{
    char isEnd;
    int type;
    int valuePtr;
    uint* float4Ptr;

    streamBegin(stream);
    streamSetHash(stream, 0x91f69a72);

    isEnd = streamIsEnd(stream);
    while (isEnd == '\0') {
        streamReadBlock(stream);
        type = streamReadType(stream);
        switch (type) {
        case 0:
            // Read string/ID and assign to name field at +0x98
            streamReadBlock(stream);
            int stringId = streamReadString(stream);
            setName(thisPtr + 0x98, stringId);
            break;
        case 1:
            // Read pointer value and store at +0x84
            valuePtr = streamReadBlock(stream);
            *(int*)(thisPtr + 0x84) = *(int*)(valuePtr + 8);
            break;
        case 2:
            // Read pointer value and store at +0x88
            valuePtr = streamReadBlock(stream);
            *(int*)(thisPtr + 0x88) = *(int*)(valuePtr + 8);
            break;
        case 3:
            // Read pointer value and store at +0x8c
            valuePtr = streamReadBlock(stream);
            *(int*)(thisPtr + 0x8c) = *(int*)(valuePtr + 8);
            break;
        case 4:
            // Read pointer value and store at +0x90
            valuePtr = streamReadBlock(stream);
            *(int*)(thisPtr + 0x90) = *(int*)(valuePtr + 8);
            break;
        case 5:
            // Read pointer value and store at +0x94
            valuePtr = streamReadBlock(stream);
            *(int*)(thisPtr + 0x94) = *(int*)(valuePtr + 8);
            break;
        case 6:
            // Read 4 floats (quaternion/vector) and store at +0xa0
            streamReadBlock(stream);
            float4Ptr = (uint*)streamReadFloat4(stream);
            *(uint*)(thisPtr + 0xa0) = float4Ptr[0];
            *(uint*)(thisPtr + 0xa4) = float4Ptr[1];
            *(uint*)(thisPtr + 0xa8) = float4Ptr[2];
            *(uint*)(thisPtr + 0xac) = float4Ptr[3];
            break;
        case 7:
            // Read 4 floats (quaternion/vector) and store at +0xb0
            streamReadBlock(stream);
            float4Ptr = (uint*)streamReadFloat4(stream);
            *(uint*)(thisPtr + 0xb0) = float4Ptr[0];
            *(uint*)(thisPtr + 0xb4) = float4Ptr[1];
            *(uint*)(thisPtr + 0xb8) = float4Ptr[2];
            *(uint*)(thisPtr + 0xbc) = float4Ptr[3];
            break;
        case 8:
            // Read uint and OR into bitfield at +0x80
            valuePtr = streamReadBlock(stream);
            *(uint*)(thisPtr + 0x80) |= *(uint*)(valuePtr + 8);
            break;
        }
        streamEndBlock(stream);
        isEnd = streamIsEnd(stream);
    }
    return;
}