// FUNC_NAME: SomeClass::getRandomItemsInRange
void __thiscall SomeClass::getRandomItemsInRange(int this, int* outBuffer)
{
    uint itemCount = *(uint*)(this + 0x19c); // number of items in array at +0x198
    if (itemCount < 2) {
        if (itemCount != 0) {
            // Only one item, process it directly
            FUN_006aedf0(**(int**)(this + 0x198) + 0x50);
        }
        return;
    }

    uint startIndex = _rand() % itemCount;
    for (uint i = startIndex; i < itemCount; i++) {
        int itemPtr = *(int*)(*(int*)(this + 0x198) + i * 4);
        int capacity = outBuffer[2];
        if (outBuffer[1] == capacity) {
            // Grow buffer (double or set to 1)
            outBuffer[2] = (capacity == 0) ? 1 : capacity * 2;
            FUN_006ad900(outBuffer[2]); // realloc
        }
        undefined8* dest = (undefined8*)(*outBuffer + outBuffer[1] * 0xc);
        outBuffer[1]++; // increment count
        if (dest != nullptr) {
            *dest = *(undefined8*)(itemPtr + 0x50);
            *(undefined4*)(dest + 1) = *(undefined4*)(itemPtr + 0x58);
        }
    }

    // Wrap around for remaining items before startIndex
    for (uint j = 0; j < startIndex; j++) {
        int itemPtr = *(int*)(*(int*)(this + 0x198) + j * 4);
        int capacity = outBuffer[2];
        if (outBuffer[1] == capacity) {
            outBuffer[2] = (capacity == 0) ? 1 : capacity * 2;
            FUN_006ad900(outBuffer[2]);
        }
        undefined8* dest = (undefined8*)(*outBuffer + outBuffer[1] * 0xc);
        outBuffer[1]++;
        if (dest != nullptr) {
            *dest = *(undefined8*)(itemPtr + 0x50);
            *(undefined4*)(dest + 1) = *(undefined4*)(itemPtr + 0x58);
        }
    }
}