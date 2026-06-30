// FUNC_NAME: GhostManager::updateGhostSlot
// Function at 0x006657c0 - Updates a ghost slot (field at +0x8) based on a source object and argument.
// thisPtr (ESI) - current object, sourcePtr (EDI) - source object, arg (stack) - reference object.
void GhostManager::updateGhostSlot(void* arg) {
    int* fieldA = (int*)((char*)arg + 8);       // +0x8 field from arg
    int* fieldB = (int*)((char*)sourcePtr + 8); // +0x8 field from source
    int* fieldThis = (int*)((char*)thisPtr + 8); // +0x8 field from this

    if (*fieldA == *fieldB) {
        // If arg's field matches source's field, copy to this and commit
        *fieldThis = *fieldA;
        FUN_0066bb40(arg); // commit/apply change
        return;
    }

    // Try to allocate a new slot/ID
    int slotId = FUN_00665c30(); // returns index or -1 if full
    if (slotId == -1) {
        // No free slot, fallback to source's field
        *fieldThis = *fieldB;
        FUN_0066c8d0(); // fallback handler (no arg? maybe implicit)
        return;
    }

    // Use arg's field and then associate it
    *fieldThis = *fieldA;
    FUN_0066c8d0(arg); // register/associate with arg
    return;
}