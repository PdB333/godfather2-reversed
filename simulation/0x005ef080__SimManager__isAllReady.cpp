// FUNC_NAME: SimManager::isAllReady
byte __fastcall SimManager::isAllReady(int thisPtr)
{
    byte result;
    byte temp;
    int currentOffset;
    int loopCount;

    // Check array of 128 elements at offset 0x65c, stride 0xf8 (248 bytes each)
    result = 1;
    currentOffset = thisPtr + 0x65c;
    loopCount = 0x80;
    do {
        temp = isSlotReady(thisPtr, currentOffset);
        result = result & temp;
        currentOffset += 0xf8;
        loopCount--;
    } while (loopCount != 0);

    // Check array of 5 elements at offset 0xa0, stride 0x30 (48 bytes each)
    currentOffset = thisPtr + 0xa0;
    loopCount = 5;
    do {
        temp = isSlotReady(thisPtr, currentOffset);
        result = result & temp;
        currentOffset += 0x30;
        loopCount--;
    } while (loopCount != 0);

    // Check array of 5 elements at offset 0x1a4, stride 0x30
    currentOffset = thisPtr + 0x1a4;
    loopCount = 5;
    do {
        temp = isSlotReady(thisPtr, currentOffset);
        result = result & temp;
        currentOffset += 0x30;
        loopCount--;
    } while (loopCount != 0);

    // Check array of 5 elements at offset 0x2a8, stride 0x30
    currentOffset = thisPtr + 0x2a8;
    loopCount = 5;
    do {
        temp = isSlotReady(thisPtr, currentOffset);
        result = result & temp;
        currentOffset += 0x30;
        loopCount--;
    } while (loopCount != 0);

    // Check four individual slots at offsets 0x428, 0x398, 0x3c8, 0x3f8
    temp = isSlotReady(thisPtr, thisPtr + 0x428);
    result = result & temp;
    temp = isSlotReady(thisPtr, thisPtr + 0x398);
    result = result & temp;
    temp = isSlotReady(thisPtr, thisPtr + 0x3c8);
    result = result & temp;
    temp = isSlotReady(thisPtr, thisPtr + 0x3f8);
    result = result & temp;

    return result;
}