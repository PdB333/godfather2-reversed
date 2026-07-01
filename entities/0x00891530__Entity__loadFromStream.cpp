// FUNC_NAME: Entity::loadFromStream
// Address: 0x00891530
// Role: Deserializes an Entity object from a binary stream (EARS serialization format)

void __thiscall Entity::loadFromStream(int this, void* stream)
{
    char isEnd;
    int nodePtr;
    char* strPtr;
    int intVal;
    char buffer[12]; // temporary buffer for reading vector data
    int dummy1, dummy2, dummy3;
    long long vecValue; // 8-byte value at offset 0x164
    int vecValueHigh;   // upper 4 bytes (offset 0x16c)

    // Begin reading the stream
    streamBeginRead(stream);
    // Read a chunk identified by hash 0xb390b11a (likely a header or initial block)
    streamReadChunk(stream, 0xb390b11a);
    streamSetReadMode(1);
    isEnd = streamIsEnd();
    if (isEnd == 0) {
        // Read a vector/struct into the temporary buffer
        streamReadNode(buffer);
        streamReadVector(buffer);
        // Store the 8-byte value at offset 0x164 (e.g., a 64-bit ID or two 32-bit values)
        *(long long*)(this + 0x164) = vecValue;
        *(int*)(this + 0x16c) = vecValueHigh;
    }
    // Read the main data chunk
    streamReadChunk(stream, 0x96a9da2c);
    isEnd = streamIsEnd();
    while (isEnd == 0) {
        streamReadNode(); // advance to next node
        int tokenType = streamGetNodeType();
        switch (tokenType) {
        case 0: // integer at +0x94
            nodePtr = streamReadNode();
            *(int*)(this + 0x94) = *(int*)(nodePtr + 8);
            break;
        case 1: // string at +0x98 (64 chars)
            streamReadNode();
            strPtr = streamGetString();
            _strncpy((char*)(this + 0x98), strPtr, 0x40);
            break;
        case 2: // string at +0xd8 (64 chars)
            streamReadNode();
            strPtr = streamGetString();
            _strncpy((char*)(this + 0xd8), strPtr, 0x40);
            break;
        case 3: // integer at +0x170
            nodePtr = streamReadNode();
            *(int*)(this + 0x170) = *(int*)(nodePtr + 8);
            break;
        case 4: // integer at +0x118
            nodePtr = streamReadNode();
            *(int*)(this + 0x118) = *(int*)(nodePtr + 8);
            break;
        case 5: // string at +0x11c (64 chars)
            streamReadNode();
            strPtr = streamGetString();
            _strncpy((char*)(this + 0x11c), strPtr, 0x40);
            break;
        case 6: // integer at +0x160
            nodePtr = streamReadNode();
            *(int*)(this + 0x160) = *(int*)(nodePtr + 8);
            break;
        case 7: // integer at +0x7c
            nodePtr = streamReadNode();
            *(int*)(this + 0x7c) = *(int*)(nodePtr + 8);
            break;
        case 8: // integer at +0x80
            nodePtr = streamReadNode();
            *(int*)(this + 0x80) = *(int*)(nodePtr + 8);
            break;
        case 9: // integer at +0x84
            nodePtr = streamReadNode();
            *(int*)(this + 0x84) = *(int*)(nodePtr + 8);
            break;
        case 10: // integer at +0x88
            nodePtr = streamReadNode();
            *(int*)(this + 0x88) = *(int*)(nodePtr + 8);
            break;
        case 11: // integer at +0x8c
            nodePtr = streamReadNode();
            *(int*)(this + 0x8c) = *(int*)(nodePtr + 8);
            break;
        case 12: // integer at +0x90
            nodePtr = streamReadNode();
            *(int*)(this + 0x90) = *(int*)(nodePtr + 8);
            break;
        case 13: // vector at +0x54 (3 floats)
            streamReadNode();
            int val = streamGetString(); // actually a vector value
            setVector3((float*)(this + 0x54), val);
            break;
        case 14: // vector at +0x5c (2 floats? or color)
            streamReadNode();
            val = streamGetString();
            setVector2((float*)(this + 0x5c), val);
            break;
        case 15: // vector at +0x64 (3 floats)
            streamReadNode();
            val = streamGetString();
            setVector3((float*)(this + 0x64), val);
            break;
        case 16: // vector at +0x6c (3 floats)
            streamReadNode();
            val = streamGetString();
            setVector3((float*)(this + 0x6c), val);
            break;
        case 17: // vector at +0x74 (3 floats)
            streamReadNode();
            val = streamGetString();
            setVector3((float*)(this + 0x74), val);
            break;
        case 18: // structure at +0x178
            nodePtr = this + 0x178;
            streamReadNode(nodePtr);
            streamReadStruct(nodePtr);
            break;
        case 19: // integer at +0x15c
            nodePtr = streamReadNode();
            *(int*)(this + 0x15c) = *(int*)(nodePtr + 8);
            break;
        }
        streamAdvance();
        isEnd = streamIsEnd();
    }
    // Finalize loading (e.g., post-process or link references)
    finalizeLoad(this);
}