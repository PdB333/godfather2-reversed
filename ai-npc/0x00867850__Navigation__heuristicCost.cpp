// FUNC_NAME: Navigation::heuristicCost
// Address: 0x00867850
// Computes a heuristic cost (modified squared distance) for pathfinding.
// The heuristic incorporates direction to nearest neighbor and a scaling factor.
int __thiscall Navigation::heuristicCost(void *thisNav, int *targetNode, float *outCost)
{
    // +0xAC flags whether the navigation system is ready
    if (*(int *)((int)thisNav + 0xAC) == 0) {
        return 1;
    }

    float startPos[3];
    float dirVec[3];
    // Get the pathfinder's current forward direction and starting position
    getForwardVector(startPos, 0);   // FUN_00875190(&local_24, 0)
    getForwardVector(dirVec, 0);     // FUN_00875190(local_c, local_18) – second call returns a direction vector

    int nodeIndex = *targetNode;
    if (nodeIndex == 0) {
        return 1;
    }

    float *nodePos = (float *)targetNode[2];
    if (nodePos == (float *)0x0) {
        return 1;
    }

    // Compute squared distance from nodePos to startPos
    float dx = nodePos[0] - startPos[0];
    float dy = nodePos[1] - startPos[1];
    float dz = nodePos[2] - startPos[2];
    *outCost = dx*dx + dy*dy + dz*dz;

    // Dot product between direction vectors and nodePos (maybe nodePos relative to target)
    float dot = dotProduct(dirVec, startPos, nodePos, &DAT_00d75690);  // FUN_004a0cd0
    // dot = absolute value
    float absDot = fabsf(dot);
    float bestHeuristic = DAT_00d5eeec;   // large initial value
    if (absDot < DAT_00d5f00c)             // threshold
    {
        // Number of neighbors stored at nodePos+5 (byte)
        byte neighborCount = *(byte *)(nodePos + 5);
        if (neighborCount != 0)
        {
            // Base offset for neighbor list (from nodeIndex)
            int neighborBase = *(int *)(nodeIndex + 0x20);
            int neighborStride = *(int *)(nodeIndex + 0x24);
            for (uint i = 0; i < neighborCount; i++)
            {
                // Compute neighbor index using a short offset at nodePos+4
                short relOffset = *(short *)(nodePos + 4) + (short)i;
                int neighborIdx = (uint)(ushort)relOffset;
                int neighborDataOffset = neighborBase + (neighborIdx * 16 + 4 + neighborStride) * 0x24;
                // neighborData points to a neighbor's data block (size 0x24)

                // Recompute dot product with this neighbor's data
                getForwardVector(dirVec, startPos);  // FUN_00875190(local_18, local_c) – swapped arguments
                float neighborDot = dotProduct(dirVec, startPos, (float *)neighborDataOffset, &DAT_00d75690);

                // Get a cost from the neighbor (context‑dependent, maybe traversal cost)
                int randomSeed = getRandomValue();   // FUN_00860800()
                int neighborCost = getNeighborCost(nodeIndex, nodePos, nodeIndex, neighborDataOffset, randomSeed); // FUN_00867760
                if (neighborCost > 4) neighborCost = 4;

                float heuristic = fabsf(neighborDot);
                float scaledCost = (float)neighborCost * DAT_00e447a4;
                if (heuristic < scaledCost) {
                    heuristic = scaledCost;
                }
                if (heuristic < bestHeuristic) {
                    bestHeuristic = heuristic;
                }
            }
        }
        else
        {
            bestHeuristic = absDot;
        }
    }

    // Final cost: (bestHeuristic * slope + intercept) * squared distance
    *outCost = (bestHeuristic * _DAT_00d75cb0 + _DAT_00d5c458) * (*outCost);
    return 1;
}