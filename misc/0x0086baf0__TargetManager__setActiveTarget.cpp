// FUNC_NAME: TargetManager::setActiveTarget
void __thiscall TargetManager::setActiveTarget(int* thisPtr, int* targetPtr)
{
    // +0x70: pointer to current linked list node (may be a head or active node)
    int** currentLink = (int**)(thisPtr + 0x70);
    // targetPtr points to an entity; target's node is at offset 0x48 (0x12 ints)
    int* newNode = nullptr;
    if (targetPtr != nullptr) {
        newNode = targetPtr + 0x12; // offset 0x48: node field within target
    }

    // Update the link if the node changed
    if (*currentLink != newNode) {
        if (*currentLink != nullptr) {
            // Free the old node (deallocation routine)
            FUN_004daf90(*currentLink);
        }
        *currentLink = newNode;
        if (newNode != nullptr) {
            // Link: store the next pointer (newNode[1]) into this's +0x74
            *(int*)(thisPtr + 0x74) = newNode[1];
            // Set the newNode's back pointer to point to this's link field
            newNode[1] = (int)currentLink;
        }
    }

    if (targetPtr != nullptr) {
        // Virtual dispatch at vtable+0x10 (index 4): bool testFlag(hash, &outPtr)
        typedef bool (__thiscall *FlagFunc)(int, int, int**);
        FlagFunc flagFunc = (FlagFunc)(*(int**)(*targetPtr))[4];
        
        int* outPtr = nullptr;
        // Hash 0xa5975eb2 likely corresponds to some flag (e.g., "isActive")
        if (flagFunc((int)targetPtr, 0xa5975eb2, &outPtr) && outPtr != nullptr) {
            // Set bit 8 (0x100) of flags at offset 200 (0xC8)
            *(unsigned short*)(thisPtr + 200) |= 0x100;
            return;
        }
        // Hash 0x55859efa likely corresponds to another flag (e.g., "isInactive")
        if (flagFunc((int)targetPtr, 0x55859efa, &outPtr) && outPtr != nullptr) {
            // Clear bit 8
            *(unsigned short*)(thisPtr + 200) &= ~0x100;
        }
    }
}