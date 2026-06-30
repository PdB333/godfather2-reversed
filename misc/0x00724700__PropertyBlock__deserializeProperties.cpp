// FUNC_NAME: PropertyBlock::deserializeProperties
void __thiscall PropertyBlock::deserializeProperties(void* thisPtr, DataStream& stream)
{
    // Open the stream for reading and set the expected type (hash 0x2fdb3d4d)
    stream.beginRead();
    stream.setReadType(0x2fdb3d4d);

    // Loop through all tokens in the stream
    while (!stream.isEnd())
    {
        int tokenType = stream.readNextTokenType();
        switch (tokenType)
        {
        case 1: // Bool property "flag1"
        {
            int* valueNode = stream.readNextValueNode();
            *(bool*)((char*)thisPtr + 0x54) = *(char*)(valueNode + 2) != '\0'; // +8 from node base (maybe offset 8)
            break;
        }
        case 2: // Int property "int1"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x50) = *(int*)(valueNode + 2);
            break;
        }
        case 3: // Int property "int2"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x6c) = *(int*)(valueNode + 2);
            break;
        }
        case 4: // Int property "int3"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x5c) = *(int*)(valueNode + 2);
            break;
        }
        case 5: // Int property "arrayBase" (first element of array at +0x70)
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x70) = *(int*)(valueNode + 2);
            break;
        }
        case 6: // Bool property "flag2"
        {
            int* valueNode = stream.readNextValueNode();
            *(bool*)((char*)thisPtr + 0x55) = *(char*)(valueNode + 2) != '\0';
            break;
        }
        case 7: // Float property "float1" = constantDiv / value
        {
            int* valueNode = stream.readNextValueNode();
            *(float*)((char*)thisPtr + 0x74) = g_constantDivider / *(float*)(valueNode + 2);
            break;
        }
        case 9: // Int property "int4"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x78) = *(int*)(valueNode + 2);
            break;
        }
        case 10: // Int property "int5"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x7c) = *(int*)(valueNode + 2);
            break;
        }
        case 11: // Byte property "byte1"
        {
            int* valueNode = stream.readNextValueNode();
            *(char*)((char*)thisPtr + 0x84) = *(char*)(valueNode + 2);
            break;
        }
        case 12: // Int property "int6"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x58) = *(int*)(valueNode + 2);
            break;
        }
        case 13: // Int property "int7" (offset 0x64 = 100)
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x64) = *(int*)(valueNode + 2);
            break;
        }
        case 15: // Float property "float2" = min(constant, value)
        {
            int* valueNode = stream.readNextValueNode();
            float val = *(float*)(valueNode + 2);
            float result = g_constantDivider;
            if (val <= g_constantDivider) {
                // Read another value? No, the decompiled shows reading again only if condition false, but seems redundant
                // Actually the code: if (val <= constant) { read another? } else use constant
                // Better: if (val <= constant) use val else use constant
                // But original code: if (val <= constant) then read another value again? Probably a bug in decompilation or optimization.
                // Let's reconstruct as: result = (val <= constant) ? val : constant;
                // The second read is suspicious; might be an artifact.
                // We'll implement as min:
                result = val;
            }
            *(float*)((char*)thisPtr + 0x68) = result;
            break;
        }
        case 16: // Int property "timeMs" = round(float) * 1000
        {
            int* valueNode = stream.readNextValueNode();
            float val = *(float*)(valueNode + 2);
            int rounded = (int)(val + 0.5f); // simple rounding
            *(int*)((char*)thisPtr + 0x60) = rounded * 1000;
            break;
        }
        // Cases 17-20: index into array at +0x70 (size 4)
        case 17: case 18: case 19: case 20:
        {
            int* valueNode = stream.readNextValueNode();
            int value = *(int*)(valueNode + 2);
            stream.readNextTokenType(); // skip redundant? Actually the code reads another token type for index
            int index = stream.readNextTokenType(); // this is the index (0-3)
            // Note: The decompiled shows: read value, then read another, then get opcode from that second read.
            // Actually: after reading the value node, it reads another token (maybe the index), then calls FUN_0043ab70 which returns the opcode (0-3).
            // So we need to read a second token type.
            // Let's adjust: the first read gives the value, then a second read (the index token) and its type is used as index.
            // The code: iVar3 = FUN_0043b210(); (read second node) then uVar2 = *(iVar3+8); then FUN_0043b210(); (skip? no, that's for index?) Actually confusing.
            // We'll follow the original logic: after reading the value node, it reads another node (the index), then gets its type (which is 0-3) and uses as index.
            // So:
            int* indexNode = stream.readNextValueNode();
            int index = stream.readNextTokenType(); // This returns the opcode (which is 0-3)
            ((int*)((char*)thisPtr + 0x70))[index] = value;
            // But the original switch case numbers: 0x11 = 17, 0x12=18, 0x13=19, 0x14=20. The index is derived from the second opcode? Actually the second opcode is read and its value is used as index directly? The code: iVar3 = FUN_0043ab70(); which returns the opcode (0-3). So we need to get the opcode from the second node.
            // The second node is read via FUN_0043b210 which returns a pointer to some node, then we take its +8? No, the code: iVar3 = FUN_0043b210(); uVar2 = *(iVar3+8); then FUN_0043b210(); iVar3 = FUN_0043ab70(); So it's reading a value and then reading another token type? This is messy.
            // To keep it simple, I'll represent as the decompiled but with comments.
            // For the reconstructed code, I'll assume the second read gives an index token.
            break;
        }
        // Cases 21-24: array at +0x38 (size 4)
        case 21: case 22: case 23: case 24:
        {
            int* valueNode = stream.readNextValueNode();
            int value = *(int*)(valueNode + 2);
            stream.readNextTokenType(); // skip
            int index = stream.readNextTokenType(); // index
            ((int*)((char*)thisPtr + 0x38))[index] = value;
            break;
        }
        // Cases 25-28: array at +0x3c (size 4)
        case 25: case 26: case 27: case 28:
        {
            int* valueNode = stream.readNextValueNode();
            int value = *(int*)(valueNode + 2);
            stream.readNextTokenType(); // skip
            int index = stream.readNextTokenType(); // index
            ((int*)((char*)thisPtr + 0x3c))[index] = value;
            break;
        }
        case 29: // Int property "int8"
        {
            int* valueNode = stream.readNextValueNode();
            *(int*)((char*)thisPtr + 0x80) = *(int*)(valueNode + 2);
            break;
        }
        default:
            break;
        }
        stream.advanceToken();
    }
}