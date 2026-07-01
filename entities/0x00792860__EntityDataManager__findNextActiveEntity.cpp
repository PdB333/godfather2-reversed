// FUNC_NAME: EntityDataManager::findNextActiveEntity
// Address: 0x00792860
// Role: Iterates over entity slots in a circular manner to find the next active entity that passes a validation check.

struct SlotArrayInfo {
    int** slotArray; // +0x00: pointer to array of entity pointers
    int slotCount;   // +0x04: number of slots
};

struct EntitySlot {
    int field0;      // +0x00: unknown
    int activeFlag;  // +0x04: non-zero if slot is active
};

// External functions (renamed for clarity)
void resetSlotIterator(uint thisPtr, SlotArrayInfo* info); // FUN_00792630
int getSlotCount(uint slotCount);                          // FUN_006eb670
int validateEntityForContext(EntitySlot* entity, uint contextId, uint extraParam); // FUN_00792290

int EntityDataManager::findNextActiveEntity(SlotArrayInfo* slotInfo, uint* outIndex, uint* outResult, uint extraParam)
{
    uint contextId = reinterpret_cast<uint>(this); // param_1 is the this pointer
    resetSlotIterator(contextId, slotInfo);

    int slotCount = slotInfo->slotCount;
    if (slotCount != 0) {
        uint currentIndex = getSlotCount(slotCount); // initial index from hash/size
        *outIndex = currentIndex;

        uint iterationCount = 0;
        do {
            EntitySlot* entity = slotInfo->slotArray[*outIndex];
            if (entity->activeFlag != 0) {
                uint validationResult = validateEntityForContext(entity, contextId, extraParam);
                *outResult = validationResult;
                if (validationResult < 0x80000000) { // success (non-negative)
                    return 1;
                }
            }
            iterationCount++;
            *outIndex = (*outIndex + 1) % slotCount;
        } while (iterationCount < slotCount);
    }
    return 0;
}