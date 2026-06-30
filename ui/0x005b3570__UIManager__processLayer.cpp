// FUNC_NAME: UIManager::processLayer
// Address: 0x005b3570
// This function iterates over a linked list of UI nodes for a given layer, 
// filters them, and inserts them into a sorted draw list.
// It uses a temporary stack buffer to reorder nodes with negative sort order.

void __thiscall UIManager::processLayer(uint layerId)
{
    // Global draw list pointer (from DAT_0119cbf0)
    void* globalDrawList = (void*)0x119cbf0;

    // Get the head of the node list from this pointer at offset 0x60
    // *this points to a vtable, *(int*)(*this + 0x60) is the list ptr
    uint* currentNode = *(uint**)(*(int*)(*this) + 0x60);

    int stackDepth = 0;                 // Number of nodes currently on the temporary stack
    int insertIndex = 0;               // Position in the sorted draw list
    int stackPointer = 0;              // Offset into stackBuffer (unused in decompiled version, but likely modified by stack functions)

    // 128-byte buffer used as a temporary stack for reordering
    byte stackBuffer[128];

    if (currentNode == nullptr) {
        goto cleanup;
    }

    do {
        // Check if bit 15 (0xF) of the first word is set (visibility/enabled flag)
        if (((~((byte)(*currentNode >> 0xF) & 1) == 0) && 
             // Additional validation function (likely checks node is on screen or active)
             (isNodeValid(currentNode) == false)) || 
             // Must match the specified layer ID
            (currentNode[0xC] != layerId)) 
        {
            goto nextNode;
        }

        // Negative sort order: needs to be inserted behind other nodes in the same layer
        if (*(int*)currentNode[0x16] < 0) {
            // Pop nodes from stack that have a larger layer ID than current node
            // and insert them at the end of the draw list
            while ((0 < stackDepth) && 
                   (**(int**)(stackPop(stackBuffer) + 0x58) < (int)currentNode[0xC])) 
            {
                insertIndex--;
                void* poppedNode = stackPop(stackBuffer);  // Actually returns pointer
                insertNodeIntoDrawList(poppedNode, globalDrawList, 0xFFFFFFFF /* -1 (end) */, insertIndex);
                stackPopDiscard(stackBuffer);              // Remove from stack
                stackDepth = stackPointer;                  // stackPointer is always 0, so this sets stackDepth to 0, breaking loop
            }
            // Insert current node at position insertIndex
            insertNodeIntoDrawList(currentNode, globalDrawList, 0 /* front? */, insertIndex);
        }
        else 
        {
            // Non-negative sort order: process node and insert at the front
            processNode(currentNode);                    // Called FUN_005b3280 – maybe sorts or updates
            insertNodeIntoDrawList(currentNode, globalDrawList, 1 /* insertion type */, insertIndex);
            insertIndex++;
            stackDepth = stackPointer;                    // stackPointer is always 0, so stackDepth becomes 0
        }

nextNode:
        currentNode = (uint*)currentNode[0x18];           // next node pointer
    } while (currentNode != nullptr);

    // Final cleanup: pop remaining stack nodes and insert at end
    while (0 < stackDepth) {
        insertIndex--;
        void* poppedNode = stackPop(stackBuffer);
        insertNodeIntoDrawList(poppedNode, globalDrawList, 0xFFFFFFFF /* end */, insertIndex);
        stackPopDiscard(stackBuffer);
        stackDepth = stackPointer;
    }

cleanup:
    finalizeDrawList();                                   // Called FUN_005b31e0 – completes the draw list
    return;
}