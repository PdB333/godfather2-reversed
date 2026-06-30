// FUNC_NAME: ResourceManager::addResourceNode
int* ResourceManager::addResourceNode(int** listHead, const ResourceData* data, int extraParam)
{
    // Allocate new node
    ResourceNode* newNode = allocateResourceNode();
    if (newNode == nullptr) {
        return 0;
    }

    // Copy data from parameter structure
    newNode->field28 = (*listHead)[1]; // e.g., some kind of identifier from list head
    const char* str = (const char*)data->name;
    int nameLen = strlen(str);
    newNode->nameHash = hashString(0, str, nameLen); // likely FNV or CRC hash
    newNode->field10 = data->value1; // e.g., integer parameter
    newNode->field14 = data->short1; // 2-byte value from offset 8
    newNode->field16 = data->short2; // 2-byte value from offset 10
    newNode->field18 = data->byte1;  // byte from offset 14

    // Initialize additional data
    initResourceData(newNode, data->value2, data->value3, data->byte2, extraParam);

    // Insert node into dormant list if not already linked
    if (newNode->field30 == 0) {
        newNode->listHeadPtr = listHead;            // pointer to head pointer (pprev)
        newNode->next = *listHead;                  // next node (or null)
        newNode->prevPtr = listHead;                // pointer to next pointer of previous node (or head)
        if (*listHead != nullptr) {
            // Update previous head's prevPtr to point to this node's next field
            (*listHead)->prevPtr = &(newNode->next);
        }
        *listHead = newNode; // new head

        // Register in hash table using hash and likely a key
        registerInHashTable(newNode->nameHash, (int*)(newNode) + 1);
    }

    return newNode;
}