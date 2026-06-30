// FUNC_NAME: ResourceManager::getResourceData
int ResourceManager::getResourceData(uint resourceId) {
    // Enter critical section
    enterCriticalSection();

    // Hash lookup: use resourceId & 0x1ff (512 slot table) to index into global hash table
    HashNode* node = globalHashTable[resourceId & 0x1ff];
    if (node) {
        // Traverse linked list to find matching ID (stored at offset +4)
        while (node) {
            if (node->id == resourceId) break;
            node = node->next; // next pointer at +8
        }
        if (node) goto found;
    }

    // Not found – create new entry via slower lookup
    node = findOrCreateEntry(resourceId); // calls FUN_00616590

found:
    // Call getDataFromNode with node, property from this+0xC, and flags (0)
    DataBlock* dataBlock = getDataFromNode(node, *(int*)((char*)this + 0xC), 0); // FUN_00616a60
    if (!dataBlock) return -1;

    // Return value stored at +4 of dataBlock
    return *(int*)((char*)dataBlock + 4);
}