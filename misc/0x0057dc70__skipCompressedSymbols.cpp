// FUNC_NAME: skipCompressedSymbols
void __fastcall skipCompressedSymbols(int unused, int maxIndex, int* cursorPtr)
{
    byte firstByte;
    byte secondByte;
    uint opcode;
    uint symbolCount;
    byte* cursor;
    byte* newCursor;
    uint dataSize;

    cursor = (byte*)*cursorPtr;
    firstByte = *cursor;
    if ((firstByte & 0xf) == 5) {
        // Multi-symbol skip: opcode 5 means repeated skip block
        symbolCount = ((uint)cursor[1] << 4) | ((uint)(firstByte >> 4));
        cursor += 2;
        if (symbolCount != 0) {
            do {
                dataSize = ((uint)cursor[1] << 4) | ((uint)(*cursor >> 4));
                symbolCount--;
                opcode = *cursor & 0xf;
                if (maxIndex <= (int)(dataSize - 1)) {
                    // Reached target: compute final position
                    newCursor = cursor + 2;
                    switch (opcode) {
                    case 0:
                        newCursor = cursor + 5;
                        break;
                    case 1:
                        newCursor = cursor + 8;
                        break;
                    case 2:
                        newCursor = cursor + 0xb;
                        break;
                    case 3:
                        newCursor = cursor + 0xe;
                        break;
                    case 4:
                        unknownFunc();
                        newCursor = newCursor + dataSize * 4;
                        break;
                    case 6:
                        newCursor = cursor + dataSize + 8;
                        break;
                    case 7:
                        newCursor = cursor + dataSize * 2 + 8;
                        break;
                    case 0xd:
                        break;
                    }
                    // Skip remaining symbols using Huffman table
                    for (; 0 < (int)symbolCount; symbolCount--) {
                        opcode = *newCursor & 0xf;
                        newCursor = newCursor +
                            (((uint)newCursor[1] << 4) | ((uint)(*newCursor >> 4))) *
                            *(int*)(&offsetTable[opcode]) +
                            *(int*)(&baseTable[opcode]);
                    }
                    *cursorPtr = (int)newCursor;
                    return;
                }
                maxIndex -= (dataSize - 1);
                cursor = cursor +
                    *(int*)(&offsetTable[opcode]) * dataSize +
                    *(int*)(&baseTable[opcode]);
            } while (0 < (int)symbolCount);
            *cursorPtr = (int)cursor;
            return;
        }
    }
    else {
        // Single symbol skip based on opcode
        switch (firstByte & 0xf) {
        case 0:
            *cursorPtr = (int)(cursor + 5);
            return;
        case 1:
            *cursorPtr = (int)(cursor + 8);
            return;
        case 2:
            *cursorPtr = (int)(cursor + 0xb);
            return;
        case 3:
            *cursorPtr = (int)(cursor + 0xe);
            return;
        case 4:
            secondByte = cursor[1];
            unknownFunc();
            *cursorPtr = (int)(cursor +
                (((uint)secondByte << 4) | ((uint)(firstByte >> 4))) * 4 + 2);
            return;
        case 6:
            *cursorPtr = (int)(cursor +
                (((uint)cursor[1] << 4) | ((uint)(firstByte >> 4))) + 8);
            return;
        case 7:
            *cursorPtr = (int)(cursor +
                (((uint)cursor[1] << 4) | ((uint)(firstByte >> 4))) * 2 + 8);
            return;
        case 0xc:
            cursor += 2;
            break;
        case 0xd:
            *cursorPtr = (int)(cursor + 2);
            return;
        }
    }
    *cursorPtr = (int)cursor;
    return;
}