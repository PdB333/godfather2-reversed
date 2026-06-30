// FUNC_NAME: PoolManager::releaseNode

// Address: 0x0071f540
// Role: Releases a node back to a pool if its type is valid. Node type field at +0x04.
// If type is 0 or 0x48 (sentinel), do nothing. Otherwise subtract 0x48 to get a base index and call helper.

void __thiscall PoolManager::releaseNode(void* thisPtr)
{
    // +0x04: node type (uint32)
    int nodeType = *(int*)((char*)thisPtr + 4);

    // Check for sentinel or invalid states
    if (nodeType != 0 && nodeType != 0x48)
    {
        // nodeType is assumed to be a positive value > 0x48 (since 0 is excluded)
        // Subtract the size of each slot (0x48) to get a slot index or offset
        int slotIndex = nodeType - 0x48;

        // Call the internal deallocation function with the computed index
        // FUN_006fa060 likely handles the actual pool deallocation by slot
        FUN_006fa060(slotIndex); // Note: argument passed in ECX? Actual calling convention unknown
    }
    // Otherwise, do nothing (invalid or already freed)
}