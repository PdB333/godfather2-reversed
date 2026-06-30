// FUNC_NAME: PropertyChunkReader::readChunkedData
void __thiscall PropertyChunkReader::readChunkedData(void* this, void* stream)
{
    int* intPtr;
    void** voidPtr;
    void* wideString;
    void*** currentBlock;
    void*** dataBlock;
    void*** tempBlock;
    bool bBitmaskMode;
    char bitmaskIndex;
    int bitmaskCount;
    void** bitmaskDataPtr;
    uint bitmaskByte;
    uint bitmaskBit;
    void** chunkData;
    short shortIndex;
    void* tempValue;
    void*** globalNodePtr;

    validateMagic(stream, 0xC7BECB2F);
    currentBlock = globalNodePtr;
    while (true) {
        if (bBitmaskMode == '\0') {
            bBitmaskMode = (*currentBlock == (void*)0x0);
        }
        else {
            bBitmaskMode = (bitmaskByte == bitmaskBit);
        }
        if (bBitmaskMode) break;

        tempBlock = &chunkData;
        if (bBitmaskMode == '\0') {
            tempBlock = currentBlock;
        }
        if (*(short*)((int)tempBlock + 6) == 0x25E3) {
            voidPtr = (void*)(uint)*(ushort*)(tempBlock + 1);
        }
        else {
            voidPtr = tempBlock[1];
        }
        switch ((int)voidPtr) {
        case 0:
            tempBlock = &chunkData;
            if (bBitmaskMode == '\0') {
                tempBlock = currentBlock;
            }
            if (*(short*)((int)tempBlock + 6) == 0x25E3) {
                if (*tempBlock == (void*)0x0) {
                    tempBlock = (void***)&DAT_00e2a89b;
                }
                else {
                    tempBlock = (void***)((int)tempBlock[2] + (int)*tempBlock);
                }
            }
            else {
                tempBlock = tempBlock + 2;
            }
            intPtr = (int*)((int)this + 0x54);
            clearString(intPtr);
            initString(intPtr);
            if ((tempBlock != (void***)0x0) && (*(char*)tempBlock != '\0')) {
                wideString = convertToWideString(tempBlock);
                setStringProperty(intPtr, wideString);
                if (*intPtr != 0) {
                    addStringToList((int)this + 0x3C, intPtr);
                }
            }
            break;
        case 1:
            tempBlock = &chunkData;
            if (bBitmaskMode == '\0') {
                tempBlock = currentBlock;
            }
            if (*(short*)((int)tempBlock + 6) == 0x25E3) {
                if (*tempBlock == (void*)0x0) {
                    tempBlock = (void***)&DAT_00e2a89b;
                }
                else {
                    tempBlock = (void***)((int)tempBlock[2] + (int)*tempBlock);
                }
            }
            else {
                tempBlock = tempBlock + 2;
            }
            initString((int)this + 0x5C);
            if ((tempBlock != (void***)0x0) && (*(char*)tempBlock != '\0')) {
                wideString = convertToWideString(tempBlock);
                setStringProperty((int)this + 0x5C, wideString);
            }
            break;
        case 2:
            tempBlock = &chunkData;
            if (bBitmaskMode == '\0') {
                tempBlock = currentBlock;
            }
            *(void***)((int)this + 100) = tempBlock[2];
            break;
        case 3:
            tempBlock = &chunkData;
            if (bBitmaskMode == '\0') {
                tempBlock = currentBlock;
            }
            *(void***)((int)this + 0x68) = tempBlock[2];
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            tempBlock = &chunkData;
            if (bBitmaskMode == '\0') {
                tempBlock = currentBlock;
            }
            dataBlock = &chunkData;
            if (bBitmaskMode == '\0') {
                dataBlock = currentBlock;
            }
            if (*(short*)((int)dataBlock + 6) == 0x25E3) {
                *(void***)((int)this + 0x4C + (uint)*(ushort*)(dataBlock + 1) * 8) = tempBlock[2];
            }
            else {
                *(void***)((int)this + 0x4C + (int)dataBlock[1] * 8) = tempBlock[2];
            }
        }
        if (bBitmaskMode == '\0') {
            if ((int)bitmaskByte < 0) {
                globalNodePtr = (void***)((int)currentBlock + (int)*currentBlock);
                advanceNode();
                currentBlock = globalNodePtr;
            }
            else if ((int)bitmaskByte < (int)(bitmaskBit - 1)) {
                bitmaskByte = bitmaskByte + 1;
                globalNodePtr = (void***)((int)currentBlock + (int)*currentBlock);
                currentBlock = (void***)((int)currentBlock + (int)*currentBlock);
            }
            else {
                globalNodePtr = (void***)&DAT_01163cf8;
                currentBlock = (void***)&DAT_01163cf8;
            }
        }
        else {
            bitmaskByte = bitmaskByte + 1;
            if (bitmaskByte != bitmaskBit) {
                shortIndex = (short)bitmaskByte;
                if ((*(byte*)((bitmaskByte >> 3) + bitmaskCount) & (byte)(1 << ((byte)bitmaskByte & 7))) == 0) {
                    tempValue = *bitmaskDataPtr;
                    chunkData = bitmaskDataPtr;
                    bitmaskDataPtr = bitmaskDataPtr + 1;
                }
                else {
                    chunkData = (void**)0x0;
                    tempValue = 0;
                }
            }
        }
    }
    return;
}