// FUNC_NAME: CNodeList::findFirstActiveNode
void CNodeList::findFirstActiveNode(void)
{
    // 'this' points to a container that holds a pointer to the first node at offset +0x8
    // Each node has a next pointer at +0x8 and an active flag at +0x15
    // Traverse the linked list until we find a node with non-zero active flag, then return.
    int currentNode = *(int *)(this + 8);   // Dereference head pointer
    char isActive = *(char *)(currentNode + 0x15);
    while (isActive == '\0') {
        currentNode = *(int *)(currentNode + 8); // Follow next pointer
        isActive = *(char *)(currentNode + 0x15);
    }
    // Loop exits when a node with non-zero active flag is found (or infinite if list is circular)
    return;
}