// FUNC_NAME: GhostManager::updateGhostState
void __thiscall GhostManager::updateGhostState(void* ghostArrayPtr, int result)
{
    // ghostArrayPtr points to a structure with:
    // +0x34: pointer to array of GhostEntry (each 12 bytes)
    // +0x38: uint32 count of entries
    unsigned int slotIndex; // passed in EAX
    GhostEntry* entry;
    GhostId localGhostId;
    GhostId* ghostId;

    if (slotIndex < *(unsigned int*)((char*)ghostArrayPtr + 0x38)) {
        entry = (GhostEntry*)(*(int*)((char*)ghostArrayPtr + 0x34) + slotIndex * 12);
        // GhostEntry layout: [type (int), id1 (int), id2 (int)]
        if (entry->type == 2) { // PENDING state
            // Virtual function at vtable+0x4: getGhostIdentifier(GhostId*)
            // It fills the provided buffer and returns its address.
            ghostId = (GhostId*)(this->vtable[1])(&localGhostId);
            if (entry->id1 == ghostId->id1 && entry->id2 == ghostId->id2) {
                if (result == 0) {
                    entry->type = 4; // REJECTED
                } else if (result == 1) {
                    entry->type = 3; // CONFIRMED
                }
            }
        }
    }
}