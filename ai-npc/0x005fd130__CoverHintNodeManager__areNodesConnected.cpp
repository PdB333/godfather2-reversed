// FUNC_NAME: CoverHintNodeManager::areNodesConnected
// Address: 0x005fd130
// Role: Checks if two cover hint nodes (by pointer) are connected via a pairwise bitmask.
// The class manages an array of nodes (stride 0x24) and a bitmask of pairwise connections.
// The bitmask is obtained from a member function (likely returning a 32-bit mask).

bool __thiscall CoverHintNodeManager::areNodesConnected(void* thisPtr, void* pNodeA, void* pNodeB)
{
    // Offset +0x20: base pointer to array of nodes (each 0x24 bytes)
    uint8_t* basePtr = *(uint8_t**)((uint8_t*)thisPtr + 0x20prop);
    // Offset +0x0c: number of nodes (ushort)
    uint16_t nodeCount = *(uint16_t*)((uint8_t*)thisPtr + 0x0c);

    // Compute indices into the array
    uint32_t indexA = ((uint8_t*)pNodeA - basePtr) / 0x24;
    uint32_t indexB = ((uint8_t*)pNodeB - basePtr) / 0x24;

    // If same node, always connected
    if (indexA == indexB)
        return true;

    // Compute the linear index of the unordered pair (min, max) in a triangular array
    uint32_t pairIndex;
    if (indexA < indexB)
    {
        // pairIndex = sum_{k=0}^{indexA-1} (nodeCount - k - 1) + (indexB - indexA - 1)
        // = ( (2*nodeCount - indexA - 1) * indexA / 2 ) - indexA - 1 + indexB
        pairIndex = ((2 * nodeCount - indexA - 1) * indexA / 2) - indexA - 1 + indexB;
    }
    else
    {
        pairIndex = ((2 * nodeCount - indexB - 1) * indexB / 2) - indexB - 1 + indexA;
    }

    // Get the bitmask of active connections (likely a 32-bit value)
    uint32_t bitmask = FUN_005fca80(); // Returns a bitmask (assumed 32-bit)

    // Check if the bit at position (pairIndex mod 32) is set
    uint8_t bitPosition = pairIndex & 0x1f;
    return (bitmask >> bitPosition) & 1;
}