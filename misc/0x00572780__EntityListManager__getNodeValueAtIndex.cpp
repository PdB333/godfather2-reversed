// FUNC_NAME: EntityListManager::getNodeValueAtIndex

// Reconstructed from Ghidra at address 0x00572780
// This function retrieves a value from a linked list node at a given index.
// It traverses a singly-linked list starting from 'this->mListHead' (offset +0x124)
// and returns the int value at offset +0x14 from the node.
//
// Note: The original assembly uses ESI as an implicit index parameter (fastcall convention).
// We represent it as a second explicit parameter.

int __fastcall getNodeValueAtIndex(void* pThis, int index)
{
    // Return -1 on invalid input or out-of-bounds
    if (pThis == nullptr || index < 0)
        return -1;

    // Get the head of the linked list from offset +0x124
    int* node = *(int**)((char*)pThis + 0x124);

    // Traverse to the index-th node (0-indexed)
    for (int i = 0; i < index; i++)
    {
        if (node == nullptr)
            return -1;
        // Each node has a next pointer at offset +0x124
        node = *(int**)((char*)node + 0x124);
    }

    if (node == nullptr)
        return -1;

    // Return the value at offset +0x14 from the node
    return *(int*)((char*)node + 0x14);
}