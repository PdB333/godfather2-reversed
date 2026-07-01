// FUNC_NAME: LinkedListHead::setHeadNode
void __thiscall LinkedListHead::setHeadNode(int thisPtr, int nodeContainer)
{
    int *headNextPtr = (int *)(thisPtr + 0x24); // +0x24: pointer to first node (head->next)
    int newNode = (nodeContainer == 0) ? 0 : (nodeContainer + 0x48); // embedded list node at offset 0x48

    if (*headNextPtr != newNode)
    {
        if (*headNextPtr != 0)
        {
            releaseLinkedListNode(headNextPtr); // release old first node
        }
        *headNextPtr = newNode; // set new head->next

        if (newNode != 0)
        {
            // +0x28: head->prev (points to last node), set to new node's previously linked node
            *(int *)(thisPtr + 0x28) = *(int *)(newNode + 4);
            // set new node's prev to point to head's next pointer (circular sentinel)
            *(int **)(newNode + 4) = headNextPtr;
        }
    }
}