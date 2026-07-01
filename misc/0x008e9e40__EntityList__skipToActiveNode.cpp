// FUNC_NAME: EntityList::skipToActiveNode
void EntityList::skipToActiveNode(Entity** currentNodePtr) {
    Entity* currentNode = *currentNodePtr;

    // Traverse linked list until we find an entity with active flag set (offset +0x25)
    while (currentNode != nullptr && currentNode->activeFlag == 0) {
        currentNode = currentNode->next; // +0x00: next pointer
    }

    *currentNodePtr = currentNode;
}