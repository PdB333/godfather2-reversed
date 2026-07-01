// FUNC_NAME: Navigation::findClosestPathNode
void __thiscall Navigation::findClosestPathNode(uint* pIndex, float** nodePositionArray, bool useDebugDistance, float* distanceArray, PathQuery* query, float maxDistance) {
    float* currentDistanceEntry;
    float* currentWaypoint;
    float* bestNode = nullptr;
    float* mindistNode = nullptr;
    uint32 bestNodeId = 0;
    bool foundBest = false;
    float bestDot = 0.0f;
    float mindot = DAT_00d5ccf8; // default large threshold
    float segmentVec[4]; // +0x20, local but uninitialized tail
    float bestSegmentVec[4];

    // Check first entry: if distance <= maxDistance and not equal
    currentDistanceEntry = (float*)((int)distanceArray + (*pIndex * 4) - 4);
    if (*currentDistanceEntry <= maxDistance && maxDistance != *currentDistanceEntry) {
        do {
            uint32 nodeCount = *pIndex;
            if (nodeCount > 9) {
                return;
            }

            // Retrieve start and end waypoints of current path segment
            float* segmentStart = *(float**)((int)nodePositionArray + nodeCount * 4 - 8);
            float* segmentEnd   = *(float**)((int)nodePositionArray + nodeCount * 4 - 4);
            segmentVec[0] = segmentEnd[0] - segmentStart[0];
            segmentVec[1] = segmentEnd[1] - segmentStart[1];
            segmentVec[2] = segmentEnd[2] - segmentStart[2];
            segmentVec[3] = 0.0f;
            normalizeVector(segmentVec, segmentVec); // FUN_0056afa0

            uint32 numCandidates = (uint32)(*(byte*)((int)query + 5));
            byte bestIsMinDist = 0;
            bool foundBetter = false;
            float localBestDot = 0.0f;

            if (numCandidates == 0) {
                return;
            }

            uint32 innerIndex = 0;
            do {
                // Retrieve candidate node from path storage
                uint32 candidateOffset = (uint32)(*(short*)((int)query + 4) + (short)innerIndex) * 0x10;
                uint32 basePtr = *(uint32*)(*(uint32*)((int)this + 0x194) + 0x24);
                uint32* candidateNodeId = (uint32*)(basePtr + candidateOffset);
                float* candidatePos = (float*)(*(uint32*)(*(uint32*)((int)this + 0x194) + 0x20) + (uint32)(*(ushort*)(candidateNodeId + 1)) * 0x24);

                int hashResult;
                int* hashPtr = nullptr;
                char hashReturn = FUN_005fd340(*(uint16*)(candidateNodeId + 2), 0xF7276BE5, &hashResult);

                if (!(hashReturn == '\0' || hashPtr == nullptr || hashResult == 0 || *(char*)(hashResult + 6) != '\x02' || *hashPtr == 0)) {
                    goto LAB_008f9558;
                }

                // Check if candidate already in output
                uint32 outCount = *pIndex;
                uint32 k = 0;
                if (outCount != 0) {
                    do {
                        if (candidatePos == nodePositionArray[k]) goto LAB_008f9558;
                        k++;
                    } while (k < outCount);
                }

                if (numCandidates == 2) {
                    bestNodeId = *candidateNodeId;
                    bestNode = candidatePos;
                    goto LAB_008f9578;
                }

                if (numCandidates > 2) {
                    float* segEnd = *(float**)((int)nodePositionArray + outCount * 4 - 4);
                    float diff[4];
                    diff[0] = segEnd[0] - candidatePos[0];
                    diff[1] = segEnd[1] - candidatePos[1];
                    diff[2] = segEnd[2] - candidatePos[2];
                    diff[3] = 0.0f;
                    normalizeVector(diff, diff);

                    // Dot product with segment direction
                    float dot = (float)((uint32)(diff[1] * segmentVec[1] + diff[0] * segmentVec[0] + diff[2] * segmentVec[2]) & DAT_00e44680);
                    if (localBestDot <= dot) {
                        bestNodeId = *candidateNodeId;
                        foundBetter = true;
                        bestNode = candidatePos;
                        localBestDot = dot;
                    }
                    if (dot <= mindot) {
                        bestIsMinDist = 1;
                        mindot = dot;
                        mindistNode = candidatePos;
                    }
                }

LAB_008f9558:
                innerIndex++;
            } while (innerIndex < numCandidates);

            if (!foundBetter) {
                return;
            }

LAB_008f9578:
            // Store best node
            nodePositionArray[*pIndex] = bestNode;
            *(uint32*)((int)distanceArray + *pIndex * 4) = bestNodeId;
            if (useDebugDistance) {
                *(float**)((int)useDebugDistance + *pIndex * 4 - 4) = (float*)(-(uint32)bestIsMinDist & (uint32)mindistNode);
            }
            (*pIndex)++;

            currentDistanceEntry = (float*)((int)distanceArray + *pIndex * 4 - 4);
            query = (PathQuery*)bestNode; // questionable: reassign query pointer to bestNode? Original: param_6 = local_50;
        } while (*currentDistanceEntry <= maxDistance && maxDistance != *currentDistanceEntry);
    }
}