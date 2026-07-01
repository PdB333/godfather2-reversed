//FUNC_NAME: LinkedList::clear
void __fastcall LinkedList::clear(int *thisPtr)
{
    // thisPtr points to the LinkedList object.
    // Layout:
    // +0x00: m_pHeader (pointer to a header struct)
    // +0x04: m_count (number of items? set to 0 at end)
    // +0x08: m_capacity (used for array zeroing)
    // +0x10: m_itemCount (decremented per node freed)

    int *header = *(int **)thisPtr[0]; // dereference m_pHeader to get the header struct
    int *currentNode = *(int **)(header + 0x14); // header->head (pointer to first node)

    while (currentNode != nullptr)
    {
        int *nextNode = *(int **)(currentNode + 0x14); // node->next (pointer to next node)
        // node->data is at offset 0x14? Actually the same offset is used for both next and data.
        // Based on the decompiled code, we call FUN_009c8f10 on the value at currentNode+0x14.
        // This is likely the data pointer stored in the node.
        FUN_009c8f10(*(int **)(currentNode + 0x14)); // destroy the data object
        FUN_009c8eb0(currentNode); // free the node itself
        thisPtr[4]--; // decrement item count
        currentNode = nextNode;
    }

    // Zero out the array of pointers in the header (used for direct access?)
    for (unsigned int i = 0; i <= (unsigned int)thisPtr[2]; i++)
    {
        *(int *)(*(int *)thisPtr[0] + 0x14 + i * 4) = 0; // header->array[i] = nullptr
    }

    thisPtr[1] = 0; // reset count to 0
}