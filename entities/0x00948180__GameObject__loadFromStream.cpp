// FUNC_NAME: GameObject::loadFromStream
// Address: 0x00948180
// Role: Deserializes a game object from a binary stream (EARS chunked format)

void __thiscall GameObject::loadFromStream(int thisPtr, void* stream)
{
    char isEnd;
    int intPtr;
    int tag;
    char* strPtr;
    int* listEntry;
    char* src;
    char* pc;
    size_t size;
    bool bVar7;
    float fVar8;
    char localBuffer[12];
    int local_1dc[28];
    float colorR, colorG, colorB;
    int dummy;

    // Begin reading the stream
    streamBeginRead(stream);
    // Read chunk header: ID 0xb390b11a, version 1
    streamReadChunkID(stream, 0xb390b11a);
    streamReadVersion(stream, 1);
    isEnd = streamIsEndOfChunk(stream);
    if (isEnd == '\0') {
        // Read a string (name?) into local buffer
        streamReadString(stream, localBuffer);
        // Set this+0x70 from the string (e.g., name or identifier)
        streamSetString(thisPtr + 0x70, localBuffer);
    }

    bVar7 = false;
    // Read another chunk: ID 0xfe6cfa1c, version 0xe
    streamReadChunkID(stream, 0xfe6cfa1c);
    streamReadVersion(stream, 0xe);
    isEnd = streamIsEndOfChunk(stream);
    if (isEnd == '\0') {
        // Read an integer into this+0x54 (type field)
        intPtr = streamReadInt(stream);
        *(int*)(thisPtr + 0x54) = *(int*)(intPtr + 8);
    }

    // Main property reading loop
    streamReadChunkID(stream, 0xfe6cfa1c);
    isEnd = streamIsEndOfChunk(stream);
    if (isEnd == '\0') {
        do {
            streamReadInt(stream); // skip? or read tag?
            tag = streamReadTag(stream); // returns case number
            switch(tag) {
            case 0:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0x50) = *(int*)(intPtr + 8);
                break;
            case 1:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xe0) = *(int*)(intPtr + 8);
                break;
            case 2:
                intPtr = streamReadInt(stream);
                fVar8 = 0.0f;
                if ((0.0f < *(float*)(intPtr + 8)) &&
                    (intPtr = streamReadInt(stream), fVar8 = DAT_00d5f4b4, *(float*)(intPtr + 8) < DAT_00d5f4b4)) {
                    intPtr = streamReadInt(stream);
                    fVar8 = *(float*)(intPtr + 8);
                }
                *(float*)(thisPtr + 0x104) = fVar8;
                break;
            case 3:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xe4) = *(int*)(intPtr + 8);
                break;
            case 4:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xe8) = *(int*)(intPtr + 8);
                break;
            case 5:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xec) = *(int*)(intPtr + 8);
                break;
            case 6:
                // Read a sub-object at this+0x14c
                streamReadInt(thisPtr + 0x14c);
                streamReadSubObject(thisPtr + 0x14c);
                break;
            case 7:
                intPtr = streamReadInt(stream);
                if (*(int*)(intPtr + 8) == 0) {
                    *(unsigned int*)(thisPtr + 0x108) &= ~2;
                } else {
                    *(unsigned int*)(thisPtr + 0x108) |= 2;
                }
                break;
            case 8:
                intPtr = streamReadInt(stream);
                if (*(int*)(intPtr + 8) == 0) {
                    *(unsigned int*)(thisPtr + 0x108) &= ~1;
                } else {
                    *(unsigned int*)(thisPtr + 0x108) |= 1;
                }
                break;
            case 9:
                streamReadInt(stream);
                tag = streamReadString(stream);
                streamSetString(thisPtr + 0x120, tag);
                break;
            case 10:
                streamReadInt(stream);
                tag = streamReadString(stream);
                streamSetString(thisPtr + 0x128, tag);
                break;
            case 11:
                streamReadInt(stream);
                tag = streamReadString(stream);
                streamSetString(thisPtr + 0x130, tag);
                break;
            case 12:
                streamReadInt(stream);
                tag = streamReadString(stream);
                streamSetString(thisPtr + 0x138, tag);
                break;
            case 13:
                streamReadInt(stream);
                tag = streamReadString(stream);
                streamSetString(thisPtr + 0x140, tag);
                break;
            case 14:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0x54) = *(int*)(intPtr + 8);
                break;
            case 15:
                // Read a color (RGB) as three floats
                streamReadInt(stream);
                streamReadFloat3(stream, &colorR);
                *(float*)(thisPtr + 0xd0) = colorR;
                *(float*)(thisPtr + 0xd4) = colorG;
                *(float*)(thisPtr + 0xd8) = colorB;
                *(int*)(thisPtr + 0xdc) = 0;
                break;
            case 16:
                if (*(int*)(thisPtr + 0x54) == 1) {
                    streamReadInt(thisPtr + 0x58);
                    streamReadSubObject(thisPtr + 0x58);
                }
                break;
            case 17:
                if (*(int*)(thisPtr + 0x54) == 2) {
                    streamReadInt(thisPtr + 0x58);
                    streamReadSubObject(thisPtr + 0x58);
                }
                break;
            case 18:
                if ((*(int*)(thisPtr + 0x54) == 5) || (*(int*)(thisPtr + 0x54) == 6)) {
                    streamReadInt(thisPtr + 0x58);
                    streamReadSubObject(thisPtr + 0x58);
                }
                break;
            case 19:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xb0) = *(int*)(intPtr + 8);
                break;
            case 20:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xc0) = *(int*)(intPtr + 8);
                break;
            case 21:
                if (*(int*)(thisPtr + 0xb8) != 0) {
                    *(int*)(thisPtr + 0xb8) = 0;
                }
                streamReadInt(stream);
                src = (char*)streamReadString(stream);
                if ((src != (char*)0x0) && (pc = src, *src != '\0')) {
                    do {
                        if ((*pc == ',') || (*pc == '\0')) {
                            size = (int)pc - (int)src;
                            if (size - 1 < 0x7f) {
                                memcpy(localBuffer, src, size);
                                localBuffer[size] = 0;
                                intPtr = streamHashString(localBuffer);
                                local_1dc[0] = intPtr;
                                if ((intPtr != 0) && (listEntry = (int*)streamAddToList(local_1dc), listEntry != (int*)0x0)) {
                                    *listEntry = intPtr;
                                }
                                src = pc + 1;
                            }
                            if (*pc == '\0') break;
                        }
                        pc = pc + 1;
                    } while( true );
                }
                break;
            case 22:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0x100) = *(int*)(intPtr + 8);
                break;
            case 23:
                // Read a 4-float vector (e.g., quaternion)
                streamReadInt(stream);
                float* vec = (float*)streamReadFloat4(stream);
                *(float*)(thisPtr + 0x10c) = vec[0];
                *(float*)(thisPtr + 0x110) = vec[1];
                *(float*)(thisPtr + 0x114) = vec[2];
                *(float*)(thisPtr + 0x118) = vec[3];
                break;
            case 24:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0x11c) = *(int*)(intPtr + 8);
                break;
            case 25:
                intPtr = streamReadInt(stream);
                bVar7 = *(int*)(intPtr + 8) != 0;
                break;
            case 26:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xf0) = *(int*)(intPtr + 8);
                break;
            case 27:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xf4) = *(int*)(intPtr + 8);
                break;
            case 28:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xf8) = *(int*)(intPtr + 8);
                break;
            case 29:
                intPtr = streamReadInt(stream);
                *(int*)(thisPtr + 0xfc) = *(int*)(intPtr + 8);
                break;
            }
            streamAdvance(stream);
            isEnd = streamIsEndOfChunk(stream);
        } while (isEnd == '\0');
        if (bVar7) {
            *(int*)(thisPtr + 0xf0) = 1;
        }
    }

    // Post-processing: if flag bit1 is set and global is non-zero, copy data
    if (((*(unsigned int*)(thisPtr + 0x108) >> 1 & 1) != 0) && (DAT_0120e93c != 0)) {
        streamCopyData(thisPtr + 0x3c, &DAT_0120e93c, 0x8000);
    }

    // Finalize loading
    streamFinalizeLoad(thisPtr);
    streamNotifyLoaded();
    return;
}