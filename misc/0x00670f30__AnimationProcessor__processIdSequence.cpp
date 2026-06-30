// FUNC_NAME: AnimationProcessor::processIdSequence
int __thiscall AnimationProcessor::processIdSequence(int thisIndex, int basePtr, short* idList)
{
    int* intPtr;
    short* idPtr;
    unsigned short* shortArray;
    int iterCount;
    short cmpResult;
    int returnVal;
    uint counter;
    int accumulator;
    short* currentId;

    iterCount = basePtr;
    returnVal = 0;
    counter = 0;
    basePtr = 0;
    accumulator = 0;
    currentId = idList;

    if (*idList != 0) {
        // Offset into an array: +0x28 = (thisIndex * 5 + 10) * 4, so we get a pointer to shorts
        shortArray = (unsigned short*)(iterCount + (thisIndex * 5 + 10) * 4);
        intPtr = (int*)(iterCount + 8);  // +0x8 is a pointer field

        do {
            idPtr = idList + (counter & 0xffff);
            cmpResult = FUN_00672900(*shortArray, intPtr, idList[counter & 0xffff]);
            if (cmpResult == 0) {
                FUN_00672750(*shortArray, intPtr, *idPtr, DAT_01127e58, &basePtr);
            }

            iterCount = *intPtr;
            // +0xe4 and +0x10c are fields of the object pointed by intPtr
            returnVal = (*(int*)(iterCount + 0xe4) + (accumulator >> 10) >> 6) + *(int*)(iterCount + 0x10c);

            // +0x64 (100) is a boolean flag
            if (*(int*)(iterCount + 100) != 0) {
                accumulator += *(int*)(iterCount + 0xd0);  // +0xd0 is a delta value
            }

            currentId++;
            counter++;
        } while (*currentId != 0);
    }

    return returnVal;
}