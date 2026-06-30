// FUNC_NAME: LinkedListNode::skipToNextActive
// Function address: 0x00694030
// Role: Traverses a singly-linked list (next at offset 0) and advances the current pointer
// until it finds a node with a non-zero flag at offset 0x29.
// The caller must pass a pointer-to-pointer (int**) so that the returned node is accessible.
// Note: The decompiled code incorrectly returns void; the intended behavior updates the
// caller's pointer. We reconstruct it as a member function that takes a double pointer.
void LinkedListNode::skipToNextActive(LinkedListNode** ppNode)
{
    // Dereference to get the current node
    LinkedListNode* node = *ppNode;
    // Check the flag at offset 0x29 (active flag)
    char isActive = *(char*)((int)node + 0x29);
    while (isActive == '\0')
    {
        // Follow the next pointer (offset 0) to the next node
        node = *(LinkedListNode**)node;
        // Check the flag again
        isActive = *(char*)((int)node + 0x29);
    }
    // Update the caller's pointer to the found active node
    *ppNode = node;
}