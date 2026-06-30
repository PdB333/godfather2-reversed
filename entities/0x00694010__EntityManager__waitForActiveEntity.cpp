// FUNC_NAME: EntityManager::waitForActiveEntity
// Function address: 0x00694010
// Role: Spin-waits until an entity in an internally linked list has its active flag (offset 0x29) set to non-zero.
// The manager stores a pointer to the first entity at offset 0x8. Each entity has a next pointer at offset 0x8 and a byte active flag at offset 0x29.

struct EntityNode {
    // +0x00: unknown data
    struct EntityNode* next;             // +0x8, pointer to next node in list
    // +0x10 to +0x28: other fields
    char activeFlag;                     // +0x29, non-zero when entity is active
};

struct EntityManager {
    // +0x00: unknown data
    EntityNode* firstEntity;             // +0x8, head of linked list of entities
    // +0x0C to end: other members

    // Busy-wait until the first active entity is found in the list.
    void waitForActiveEntity() {
        EntityNode* currentNode = this->firstEntity;           // get head node
        char active = currentNode->activeFlag;                 // check active flag
        while (active == '\0') {
            currentNode = currentNode->next;                   // move to next node
            active = currentNode->activeFlag;                  // re-check flag
        }
        // After loop, currentNode is the first active entity (not returned or used here)
    }
};