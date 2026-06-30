// FUNC_NAME: ObjectListManager::processObjectsByPriority
void ObjectListManager::processObjectsByPriority(int priorityThreshold) {
    int* hashTable = g_objectHashTable; // DAT_012058e0 - array of linked list heads (0x1000 entries)
    ObjectNode* currentNode = getFirstObject(); // FUN_00611220 - get head of current list

    if (currentNode != nullptr) {
        do {
            ObjectNode* nextNode = currentNode->next; // +0x38

            // Find first non-empty bucket in hash table (if hashTable exists)
            if (hashTable != nullptr) {
                for (uint bucketIndex = 0; bucketIndex < 0x1000; bucketIndex++) {
                    if (hashTable[bucketIndex] != 0) {
                        // This bucket is used, but we don't actually use it here? 
                        // Possibly a bug in decompilation or leftover code.
                        break;
                    }
                }
            }

            // Check if object's priority is within [priorityThreshold, 3]
            if ((priorityThreshold <= currentNode->priority) && (currentNode->priority < 4)) {
                setObjectActive(currentNode->objectId, false); // FUN_006065a0 - deactivate object
            }

            currentNode = nextNode;
        } while (currentNode != nullptr);
    }
}