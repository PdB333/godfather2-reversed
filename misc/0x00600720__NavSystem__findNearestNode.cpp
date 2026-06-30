// FUNC_NAME: NavSystem::findNearestNode
char __thiscall NavSystem::findNearestNode(NavSystem* this, const float* position, NavCell* cell, NavList* resultList, NodeFilter* filter) {
    char found = 0;
    if (cell != nullptr) {
        float px = position[0];
        float py = position[1];
        float pz = position[2];

        float bestDist = 0.0f;
        uint32_t cellIndex = 0;

        // Iterate over nodes in the cell (offset +0x20 is array of nodes, count at +0x0c)
        if (cell->nodeCount != 0) {
            int32_t nodeOffset = 0;
            do {
                // Base pointer to node array (+0x20)
                uint8_t* nodeBase = cell->nodeArray;
                NavNode* node = (NavNode*)(nodeBase + nodeOffset);

                // Node position (offsets 0x00, 0x04, 0x08)
                float dx = px - node->x;
                float dy = py - node->y;
                float dz = pz - node->z;
                float sqDist = dx*dx + dy*dy + dz*dz;

                // Check if this node is valid (non-zero at +0x14) and better than current best
                if ((found == 0 || sqDist < bestDist) && node->validFlag != 0) {
                    // Get the sub-index field at +0x10
                    uint16_t subIndex = node->subIndex;
                    // Pointer to sub-node array (+0x24)
                    NavSubNode* subArray = cell->subNodeArray;
                    uint32_t subCount = node->subCount; // from +0x14 (actually byte? but used as loop bound)

                    // Try each sub-node until one is not skipped
                    uint32_t subIdx = 0;
                    do {
                        // subIndex + subIdx (byte used as counter loop)
                        uint16_t effectiveIdx = subIndex + (uint16_t)subIdx;
                        NavSubNode* subNode = &subArray[effectiveIdx]; // each 0x24 bytes

                        // Check if this sub-node is blocked (flag 0x4000 at offset +0x18)
                        if ((subNode->flags & 0x4000) == 0) {
                            // Check if the sub-node is already used by some previous query in this frame
                            // (based on this->field_0xb4 bit 1)
                            if ((this->someBitfield >> 1 & 1) == 0) {
                                // Get current path node for source and target
                                uint32_t* currentPathNode = (this->sourceNodeCount != 0) ? this->sourceNodeArray : nullptr;
                                uint32_t currentPathSubNode = (this->sourceNodeCount != 0) ? this->sourceNodeIndices : 0;

                                // Check if this node/subnode is already in the path (source or target)
                                bool alreadyUsed = false;
                                if (cell == this->sourceCell && subNode == this->sourceSubNode) {
                                    alreadyUsed = true;
                                } else if (cell == this->targetCell && subNode == this->targetSubNode) {
                                    alreadyUsed = true;
                                }
                                if (alreadyUsed) goto skipSubNode;
                            }

                            // Temporarily modify cell's linked list head to simplify list operations
                            // (uses stack variable as sentinel to avoid null checks)
                            uint32_t oldCellHead = cell->linkedListHead;
                            cell->linkedListHead = (uint32_t)&resultList; // stack address

                            // If filter callback is null or approves the node
                            if (filter == nullptr || filter(this, &resultList, &sqDist) != 0) {
                                // Found a new candidate; remove old from list if present
                                if (found == 0 || sqDist < bestDist) {
                                    // Remove previous node from resultList if exists
                                    uint32_t oldNode = resultList->node;
                                    if (resultList != &oldNode && oldNode != oldCellHead) { // [1] – simplified
                                        // Remove oldNode from the linked list
                                        uint32_t* prev = (uint32_t*)oldNode[1]; // offset +4
                                        while (prev != resultList) { // traverse
                                            prev = (uint32_t*)prev[1];
                                        }
                                        prev[1] = resultList->next;
                                    }
                                    // Insert new node at head of list
                                    resultList->node = oldCellHead;
                                    resultList->next = (oldCellHead != 0) ? *(uint32_t*)(oldCellHead + 4) : 0;
                                    if (oldCellHead != 0) {
                                        *(uint32_t*)(oldCellHead + 4) = (uint32_t)resultList;
                                    }
                                    resultList->data = (uint32_t)subNode; // store sub-node pointer
                                    bestDist = sqDist;
                                    found = 1;
                                }

                                // Restore cell's linked list head
                                if (oldCellHead != 0) {
                                    uint32_t* prev = (uint32_t*)(*(uint32_t*)(oldCellHead + 4));
                                    if (prev == &oldCellHead) {
                                        *(uint32_t*)(oldCellHead + 4) = oldCellHead;
                                    } else {
                                        while ((uint32_t*)prev[1] != &oldCellHead) {
                                            prev = (uint32_t*)prev[1];
                                        }
                                        prev[1] = oldCellHead;
                                    }
                                }
                            } else {
                                // Filter rejected; restore list head
                                if (oldCellHead != 0) {
                                    uint32_t* prev = (uint32_t*)(*(uint32_t*)(oldCellHead + 4));
                                    if (prev != &oldCellHead) {
                                        while ((uint32_t*)prev[1] != &oldCellHead) {
                                            prev = (uint32_t*)prev[1];
                                        }
                                        prev[1] = oldCellHead;
                                    }
                                }
                                // [2] – there is a second path similar to first
                            }
                        }
skipSubNode:
                        subIdx++;
                    } while (subIdx < node->subCount);
                }

                cellIndex++;
                nodeOffset += 0x24; // sizeof(NavNode)
            } while (cellIndex < cell->nodeCount);
        }
    }

    // If nothing found, clear the result list
    if (found == 0) {
        uint32_t oldNode = resultList->node;
        if (oldNode != 0) {
            uint32_t* prev = (uint32_t*)(*(uint32_t*)(oldNode + 4));
            if (prev == resultList) {
                *(uint32_t*)(oldNode + 4) = resultList->next;
            } else {
                while ((uint32_t*)prev[1] != resultList) {
                    prev = (uint32_t*)prev[1];
                }
                prev[1] = resultList->next;
            }
            resultList->node = 0;
        }
        resultList->data = 0;
    }
    return found;
}