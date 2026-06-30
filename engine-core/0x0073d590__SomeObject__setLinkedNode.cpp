// FUNC_NAME: SomeObject::setLinkedNode
void __thiscall SomeObject::setLinkedNode(int param_1, int param_2)
{
    int **listNodePtr; // pointer to the node pointer at offset 0x64 (100)
    int *newNode;      // the node to assign

    listNodePtr = (int **)(param_1 + 100); // +0x64: pointer to linked list node

    // If param_2 is null, the node is null; otherwise, adjust to point to the embedded list node at offset 0x48
    if (param_2 == 0) {
        newNode = 0;
    } else {
        newNode = (int *)(param_2 + 0x48); // +0x48: offset to link node within the object
    }

    // If the current node pointer is different from the new one, update it
    if (*listNodePtr != newNode) {
        // If there's an existing node, remove it from the list
        if (*listNodePtr != 0) {
            removeNodeFromList(listNodePtr); // FUN_004daf90: unlink the current node
        }
        // Set the new node pointer
        *listNodePtr = newNode;
        if (newNode != 0) {
            // Set the 'next' pointer of the object at offset 0x68 to the new node's next (at newNode+4)
            *(int **)(param_1 + 0x68) = (int *)*((int *)newNode + 1); // *(undefined4 *)(param_2 + 0x4c) but careful: newNode+4
            // Point the node's 'prev' (or list head) back to the node pointer location
            *((int **)newNode + 1) = listNodePtr; // *(int **)(newNode + 4) = listNodePtr
        }
    }
    return;
}