// FUNC_NAME: EntityManager::destroyEntity
void __thiscall EntityManager::destroyEntity(EntityManager* this, Entity* entity) {
    // +0x48: m_bAudioEnabled? Check if audio should be stopped
    if (*(char*)((int)this + 0x48) != '\0') {
        // Stop audio associated with entity (handle at +0x164)
        stopAudio(0, *(int*)((int)entity + 0x164)); // FUN_00950be0
    }

    // Entity has an intrusive list node at offset +0x48
    ListNode* entityNode;
    if (entity == nullptr) {
        entityNode = nullptr;
    } else {
        entityNode = (ListNode*)((int)entity + 0x48);
    }

    // Save the next pointer and then mark node as removed (self-referential sentinel)
    int savedNext = *(int*)(entityNode + 4); // +0x04: next pointer
    *(int**)((int)entityNode + 4) = &entityNode; // Set next to stack address (self marker)

    // Search in the manager's node array for the matching node
    uint index = 0;
    if (*(uint*)((int)this + 0x60) != 0) { // +0x60: m_nodeCount
        int* nodeArray = *(int**)((int)this + 0x5c); // +0x5c: m_nodes (array of pairs: [nodePtr, ?])
        do {
            if (nodeArray[0] == (int)entityNode) { // first element is the node pointer
                if (index != 0xffffffff) {
                    removeNodeAtIndex(index); // FUN_00920d30
                }
                break;
            }
            index++;
            nodeArray += 2; // each entry is 2 ints
        } while (index < *(uint*)((int)this + 0x60));
    }

    // Finalize destruction of the node (likely deallocation)
    if (entityNode != nullptr) {
        finalizeNodeDestruction(&entityNode); // FUN_004daf90 (passes address of local pointer)
    }
}