// FUNC_NAME: EntityManager::removeEntityHandle
void __thiscall EntityManager::removeEntityHandle(int this_ecx, int entityID)
{
    uint count = *(uint *)(this_ecx + 0x90c); // Number of active entity handles
    uint index = 0;

    if (count != 0) {
        int *arrayStart = (int *)(this_ecx + 0x8fc); // Base of the entity handle array
        do {
            if (*arrayStart == entityID) {
                break;
            }
            index++;
            arrayStart++;
        } while (index < count);
    }

    if (index < count) {
        // Remove the found element by shifting the remainder left
        index++; // Move to the next element after the one to remove
        if (index < count) {
            uint *srcPtr = (uint *)(this_ecx + 0x8f8 + index * 4); // Starting at the element after the removed one
            do {
                *srcPtr = srcPtr[1]; // Shift left
                index++;
                srcPtr++;
            } while (index < *(uint *)(this_ecx + 0x90c)); // Original count still in memory during shift
        }
        *(int *)(this_ecx + 0x90c) = *(int *)(this_ecx + 0x90c) - 1; // Decrement count
    }
}