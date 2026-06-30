// FUNC_NAME: StreamManager::releaseCurrentSlotResources
void StreamManager::releaseCurrentSlotResources(void)
{
    // Check if the audio object manager singleton is valid
    if (audioObjMgrSingleton == (void*)audioObjMgrVTablePtr) {
        // +0x00 in the slot array: first resource pointer
        int* resource1 = *(int**)((int)&slotArray + currentSlot * 0x38);
        if (resource1 != 0) {
            releaseResource(audioManagerInstance, resource1);
        }
        // Re-check (unlikely) and handle second resource at +0x04
        if (audioObjMgrSingleton == (void*)audioObjMgrVTablePtr) {
            int* resource2 = *(int**)((int)&slotArray + currentSlot * 0x38 + 4);
            if (resource2 != 0) {
                releaseResource2(audioManagerInstance, resource2);
            }
        }
    }
}