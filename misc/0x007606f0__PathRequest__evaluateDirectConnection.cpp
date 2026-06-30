// FUNC_NAME: PathRequest::evaluateDirectConnection

// Reconstructed from Ghidra at 0x007606f0
// The function checks a direct connection between two path nodes for a given path request.
// Returns 1 if the connection is valid, 0 otherwise.
// On success, *outCost contains the heuristic cost of the connection.

int __thiscall PathRequest::evaluateDirectConnection(
    void* thisPtr,               // param_1: PathRequest object
    PathConnection* connection,  // param_2: connection descriptor
    PathData* pathData,          // param_3: path data container
    float* outCost)              // param_4: output cost
{
    uint allowedFlags = *(uint*)((uintptr_t)thisPtr + 0x20);
    ushort connectionFlags = *(ushort*)((uintptr_t)connection + 10);
    
    // If the connection's flags are not in the allowed set, skip.
    if ((allowedFlags & (uint)connectionFlags) != 0)
        return 0;
    
    // Get indices of the two nodes
    ushort nodeIndex1 = *(ushort*)((uintptr_t)connection + 4);
    ushort nodeIndex2 = *(ushort*)((uintptr_t)connection + 6);
    
    // Compute pointers to node structures (each node is 0x24 bytes)
    void* node1 = (void*)(*(int*)((uintptr_t)pathData + 0x20) + (uint)nodeIndex1 * 0x24);
    void* node2 = (void*)(*(int*)((uintptr_t)pathData + 0x20) + (uint)nodeIndex2 * 0x24);
    
    int movementType = *(int*)((uintptr_t)thisPtr + 4);
    
    // If movement type is not empty and not vehicle (0x48), perform a line-of-sight check.
    if ((movementType != 0) && (movementType != 0x48))
    {
        // Get the global path manager singleton
        void* pathManager = getPathManagerSingleton(); // FUN_00471610
        // Check if direct line exists (using manager's internal data)
        float visDist = checkDirectLineOfSight(
            (int*)((uintptr_t)pathManager + 0x30),
            node1, node2, 0, 1); // FUN_0084cb90
        if (visDist < g_maxDirectDistance) // _DAT_00e51b28
            return 0;
    }
    
    // Compute cost between nodes using the connection's own cost factor (from connection->cost at offset 0)
    float cost = computeNodeConnectionCost(node1, node2, *(uint*)connection); // FUN_00760570
    *outCost = cost;
    return 1;
}