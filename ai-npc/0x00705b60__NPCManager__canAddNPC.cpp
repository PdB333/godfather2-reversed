// FUNC_NAME: NPCManager::canAddNPC
bool __thiscall NPCManager::canAddNPC(void* this, uint slotIndex, uint requestCount)
{
    int slotPointer;

    // Slot index must be in range 0-5
    if (5 < slotIndex) {
        return false;
    }

    // Access slot array at this+0x18, each slot entry is 0x14 bytes
    // Each entry contains a pointer at offset 0 within the entry
    if ((slotIndex < 0xb) && 
        (slotPointer = *(int*)((char*)this + 0x18 + slotIndex * 0x14), 
         slotPointer != 0) && 
        (slotPointer != 0x48) && 
        (requestCount <= *(uint*)(slotPointer + 0x4c8))) {
        // Check global capacity limits (e.g., total NPC count)
        uint currentCount = getCurrentGlobalCount();
        uint maxCount = getMaxGlobalCount();
        return currentCount < maxCount;
    }
    // Slot is empty, invalid, or request exceeds per-slot limit -> allow
    return true;
}