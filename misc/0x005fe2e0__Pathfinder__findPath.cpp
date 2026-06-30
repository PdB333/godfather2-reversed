// FUNC_NAME: Pathfinder::findPath
// Address: 0x005fe2e0
// This function implements an A* pathfinding search over a navigation graph.
// It takes a navigation graph (param_2), a flag (param_4), and outputs a linked list of path nodes (param_3).
// Returns 1 if a path was found, 0 otherwise.

int Pathfinder::findPath(int this, int* navGraph, int** outPathList, char allowSearch)
{
    float bestScore;
    int i;
    int neighborIndex;
    int neighborCost;
    int nodeFlags;
    int heuristic;
    int totalCost;
    int* neighborData;
    int* bestNode;
    int loopCount;
    int* tempListHead;
    int* tempListTail;
    int* tempListCurr;
    int insertedNode;
    int prevNode;
    int someNodeData;
    float randomFloat;
    uint blockedMask;
    bool allowFlag;

    // +0x24 in navGraph: base of neighbor array (each neighbor block 0x10 bytes)
    // +0x20 in navGraph: base of node array (each node 0x24 bytes)
    int* nodeArray = navGraph[0]; // *param_2
    int* neighborBase;
    int* nodeBase;
    if ((nodeArray != 0) && (int* neighborData2 = navGraph[2], neighborData2 != 0)) {
        int* cachePtr = *(int**)(this + 0x118);
        if (cachePtr == 0) {
            // Determine allowFlag: if allowSearch is false OR (nodeFlags & 0x4000) != 0, then allowFlag=0
            if ((allowSearch == '\0') || 
                (allowFlag = 1, (*(ushort*)(neighborData2 + 0x18) & 0x4000) != 0)) {
                allowFlag = 0;
            }
            byte numNeighbors = *(byte*)(neighborData2 + 0x14); // number of neighbors (first iteration)
            tempListHead = 0;
            tempListTail = 0;
            tempListCurr = 0;
            bestScore = -127.0f; // sentinel very bad score
            i = 0;
            if (numNeighbors != 0) {
                do {
                    neighborIndex = (ushort)(*(short*)(neighborData2 + 0x10) + (short)i);
                    neighborData = (int*)(neighborIndex * 0x10 + *(int*)(nodeArray + 0x24));
                    blockedMask = *(uint*)(this + 0x114);
                    nodeFlags = *(ushort*)(neighborData + 10);
                    if ((blockedMask & nodeFlags) == 0) {
                        neighborCost = *(ushort*)(neighborData + 4); // cost from neighbor data
                        nodeBase = (int*)(*(int*)(nodeArray + 0x20) + (uint)neighborCost * 0x24);
                        heuristic = Pathfinder::heuristicScore(allowFlag);
                        if (heuristic >= 0) {
                            Pathfinder::openNode(nodeArray, nodeBase); // add node to open list
                            int (*costFunc)(int,int,int*) = *(int(**)(int,int,int*))(this + 0xa0);
                            totalCost = costFunc(this, navGraph, (int*)&bestNode); // compute f = g + h
                            if ((bestScore <= totalCost) && 
                                ((bestScore < totalCost) ||
                                 (randomFloat = Random::getFloat(), randomFloat < 0x00e2cd54))) { // tie-breaking
                                Pathfinder::updateBestScore(&bestNode);
                                bestScore = totalCost;
                            }
                            Pathfinder::closeNode(); // pop from open list
                        }
                    }
                    i = i + 1;
                } while (i < numNeighbors);
            }

            // Second iteration for path smoothing (if flag enabled)
            if ((*(uint*)(this + 0xb4) >> 10 & 1) != 0) {
                insertedNode = 0;
                prevNode = 0;
                someNodeData = 0;
                loopCount = (uint)*(byte*)(neighborData2 + 0x1c) + (uint)*(byte*)(neighborData2 + 0x15);
                i = 0;
                if (loopCount != 0) {
                    do {
                        neighborIndex = (ushort)(*(short*)(neighborData2 + 0x16) + (short)i);
                        neighborData = (int*)(neighborIndex * 0x10 + *(int*)(nodeArray + 0x30));
                        nodeFlags = *(ushort*)(neighborData + 10);
                        if ((*(uint*)(this + 0x114) & nodeFlags) == 0) {
                            int* nodeInfo = Pathfinder::getLinkedNode(&bestNode, neighborData); // returns a triple (first, prev, data)
                            if ((&insertedNode != nodeInfo) && (i = *nodeInfo, insertedNode != i)) {
                                if (insertedNode != 0) {
                                    Pathfinder::removeFromList(&insertedNode);
                                }
                                insertedNode = i;
                                if (i != 0) {
                                    prevNode = *(int*)(i + 4);
                                    *(int**)(i + 4) = &insertedNode;
                                }
                            }
                            someNodeData = nodeInfo[2];
                            // Reattach bestNode linked list if needed (complex pointer juggling)
                            if (bestNode != 0) {
                                int* listPtr = *(int**)(bestNode + 4);
                                if (listPtr == &bestNode) {
                                    *(int*)(bestNode + 4) = *(int*)(&someNodeData); // iStack_10?
                                } else {
                                    while ((int*)listPtr[1] != &bestNode) {
                                        listPtr = (int*)listPtr[1];
                                    }
                                    listPtr[1] = *(int*)(&someNodeData);
                                }
                            }
                            // If we have an inserted node and heuristic is valid, compute cost and check if better
                            if ((insertedNode != 0) && 
                                (heuristic = Pathfinder::heuristicScore(allowFlag), heuristic >= 0)) {
                                int (*costFunc)(int,int,int*) = *(int(**)(int,int,int*))(this + 0xa0);
                                totalCost = costFunc(this, navGraph, &insertedNode);
                                if ((bestScore <= totalCost) && 
                                    ((bestScore < totalCost) ||
                                     (randomFloat = Random::getFloat(), randomFloat < 0x00e2cd54))) {
                                    Pathfinder::updateBestScore(&insertedNode);
                                    bestScore = totalCost;
                                }
                            }
                        }
                        i = i + 1;
                    } while (i < loopCount);
                    // Clean up the temporary list (insertedNode list fix)
                    if (insertedNode != 0) {
                        int* listPtr = *(int**)(insertedNode + 4);
                        if (listPtr == &insertedNode) {
                            *(int*)(insertedNode + 4) = prevNode;
                        } else {
                            while ((int*)listPtr[1] != &insertedNode) {
                                listPtr = (int*)listPtr[1];
                            }
                            listPtr[1] = prevNode;
                        }
                    }
                }
            }

            // If best path found, attach the list to output
            tempListHead = tempListHead; // local_2c
            if (bestScore >= 0) {
                if ((outPathList != &tempListHead) && (*outPathList != tempListHead)) {
                    if (*outPathList != 0) {
                        Pathfinder::removeFromList(outPathList);
                    }
                    *outPathList = tempListHead;
                    if (tempListHead != 0) {
                        outPathList[1] = (int*)tempListHead[1];
                        tempListHead[1] = (int)outPathList;
                    }
                }
                outPathList[2] = tempListTail;
                if (tempListHead != 0) {
                    int** listPrevPtr = (int**)tempListHead[1];
                    if (listPrevPtr == &tempListHead) {
                        tempListHead[1] = (int)tempListTail;
                        return 1;
                    }
                    while ((int**)listPrevPtr[1] != &tempListHead) {
                        listPrevPtr = (int**)listPrevPtr[1];
                    }
                    listPrevPtr[1] = tempListTail;
                }
                return 1;
            } else {
                // No path found, clean up list
                if (tempListHead != 0) {
                    int** listPrevPtr = (int**)tempListHead[1];
                    if (listPrevPtr == &tempListHead) {
                        tempListHead[1] = (int)tempListTail;
                        return 0;
                    }
                    while ((int**)listPrevPtr[1] != &tempListHead) {
                        listPrevPtr = (int**)listPrevPtr[1];
                    }
                    listPrevPtr[1] = tempListTail;
                }
                return 0;
            }
        } else {
            // Alternative path: cache-based path generation
            int maxCount = (*(int(**)(void))(*(int*)*cachePtr + 8))();
            if (*(uint*)(this + 0x120) < maxCount - 1) {
                int newNode = (*(int(**)(uint))(*(int*)*cachePtr + 0xc))(*(uint*)(this + 0x120) + 1);
                Pathfinder::updateBestScore(newNode);
                if ((*outPathList != 0) && (outPathList[2] != 0)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}