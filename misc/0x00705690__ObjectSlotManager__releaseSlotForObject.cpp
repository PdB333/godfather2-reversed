// FUNC_NAME: ObjectSlotManager::releaseSlotForObject
void __thiscall ObjectSlotManager::releaseSlotForObject(int thisPtr, int objectPtr)
{
    int slotIndex;
    int slotBase;
    int slotRefCount;
    int objectInSlot;
    int *slotObjectPtrField;
    char objectTag;
    int currentSlot;
    int currentObject;

    if (objectPtr != 0) {
        slotIndex = getSlotIndex(objectPtr);
        slotBase = thisPtr + slotIndex * 0x14;
        objectInSlot = *(int *)(slotBase + 0x18); // +0x18: stored object pointer / ID
        if (objectInSlot == 0) {
            slotRefCount = 0;
        } else {
            slotRefCount = objectInSlot - 0x48; // adjust pointer to match objectPtr
        }
        if (objectPtr == slotRefCount) {
            // decrement reference count at +0x20
            if (*(int *)(slotBase + 0x20) != 0) {
                *(int *)(slotBase + 0x20) = *(int *)(slotBase + 0x20) - 1;
            }
            slotObjectPtrField = (int *)(slotBase + 0x18);
            if (((*(int *)(slotBase + 0x18) != 0) && (*(int *)(slotBase + 0x18) != 0x48)) && (*slotObjectPtrField != 0)) {
                freeSlotMemory(slotObjectPtrField); // FUN_004daf90
                *slotObjectPtrField = 0;
            }
            objectTag = *(char *)(objectPtr + 0x1ad); // +0x1ad: tag or ID
            currentSlot = 0;
            int maxSlots = *(int *)(*(int *)(thisPtr + 0x10) + 4); // +0x10: pointer to slot array header with count at offset 4
            if (maxSlots != 0) {
                do {
                    currentObject = getObjectBySlotIndex(currentSlot); // FUN_00704110
                    if ((currentObject != 0) && 
                        (*(char *)(currentObject + 0x1ad) == objectTag) && 
                        (getSlotIndex(currentObject) == slotIndex)) {
                        releaseSlotObject(currentObject); // FUN_00704ca0
                    }
                    currentSlot++;
                } while (currentSlot < maxSlots);
            }
        }
    }
    return;
}