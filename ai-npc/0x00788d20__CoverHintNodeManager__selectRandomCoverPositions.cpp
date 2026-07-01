// FUNC_NAME: CoverHintNodeManager::selectRandomCoverPositions
void __thiscall CoverHintNodeManager::selectRandomCoverPositions(int* this, PositionArray* outPositions)
{
    CoverNode* head = (CoverNode*)*this;
    int nodeCount = 0;
    CoverNode* current = head;

    // Count nodes in linked list
    if (head != nullptr) {
        do {
            current = current->next;
            nodeCount++;
        } while (current != nullptr);

        if (nodeCount > 1) {
            // Randomly select one node index
            uint randomVal = _rand();
            CoverNode* selectedNode = nullptr;
            uint index = 0;
            float minDistSq = DAT_00d5ddec; // Global minimum distance squared

            // First pass: try to add the randomly selected node if it's far enough from existing positions
            for (CoverNode* node = head; node != nullptr; node = node->next) {
                if (randomVal % nodeCount == index) {
                    selectedNode = node;
                }
                if (selectedNode != nullptr) {
                    // Check distance to all existing positions in the array
                    uint existingCount = outPositions->count;
                    uint i = 0;
                    if (existingCount != 0) {
                        Vector3* posArray = outPositions->data;
                        do {
                            float dx = node->x - posArray[i].x;
                            float dy = node->y - posArray[i].y;
                            float dz = node->z - posArray[i].z;
                            if (dx*dx + dy*dy + dz*dz < minDistSq) {
                                goto skipAdd; // Too close, skip
                            }
                            i++;
                        } while (i < existingCount);
                    }

                    // If we get here, node is far enough; add it
                    uint capacity = outPositions->capacity;
                    if (existingCount == capacity) {
                        // Reallocate array (double capacity)
                        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
                        FUN_006ad900(newCapacity); // Reallocation function
                        minDistSq = DAT_00d5ddec; // Refresh global (maybe volatile)
                    }
                    Vector3* newPos = outPositions->data + outPositions->count * sizeof(Vector3);
                    outPositions->count++;
                    if (newPos != nullptr) {
                        newPos->x = node->x;
                        newPos->y = node->y;
                        newPos->z = node->z;
                    }
                }
skipAdd:
                index++;
            }

            // Second pass: add all other nodes (excluding the selected one) if they are far enough
            CoverNode* node = head;
            do {
                if (node == nullptr || node == selectedNode) {
                    return;
                }
                // Check distance to existing positions
                uint existingCount = outPositions->count;
                uint i = 0;
                if (existingCount != 0) {
                    Vector3* posArray = outPositions->data;
                    do {
                        float dx = node->x - posArray[i].x;
                        float dy = node->y - posArray[i].y;
                        float dz = node->z - posArray[i].z;
                        if (dx*dx + dy*dy + dz*dz < minDistSq) {
                            goto skipAdd2;
                        }
                        i++;
                    } while (i < existingCount);
                }

                // Add node if far enough
                uint capacity = outPositions->capacity;
                if (existingCount == capacity) {
                    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
                    FUN_006ad900(newCapacity);
                    minDistSq = DAT_00d5ddec;
                }
                Vector3* newPos = outPositions->data + outPositions->count * sizeof(Vector3);
                outPositions->count++;
                if (newPos != nullptr) {
                    newPos->x = node->x;
                    newPos->y = node->y;
                    newPos->z = node->z;
                }
skipAdd2:
                node = node->next;
            } while (true);
        }
    }

    // Fallback: if list has 0 or 1 node, add the first node's position directly
    FUN_006aedf0(&head->x); // head+3 is the position of the first node
}