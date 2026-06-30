// FUNC_NAME: SomeManager::releaseFirstActiveSlot
int __fastcall SomeManager::releaseFirstActiveSlot(int thisPtr, int param_2) // param_2 unused, likely this* was in ecx, param_2 is edx but not used
{
    int index;
    int* stateArray;
    int baseOffset;

    index = 0;
    stateArray = (int*)(thisPtr + 0x488); // array of 5 states, each entry stride 0x129 ints = 0x4A4 bytes
    do {
        if (*stateArray == 3) { // active slot found
            baseOffset = index * 0x4A4 + thisPtr;
            releaseResource(*(int*)(index * 0x4A4 + thisPtr + 0x26C)); // +0x26C: some resource handle/pointer
            processRemoval(); // cleanup step
            queueRefresh(); // first call
            queueRefresh(); // second call (maybe double buffering)
            *(int*)(baseOffset + 0x200) = 0; // +0x200: slot field A
            *(int*)(baseOffset + 0x204) = 0; // +0x204: slot field B
            return index;
        }
        index++;
        stateArray += 0x129; // advance to next slot's state
    } while (index < 5);
    return -1; // no active slot found
}