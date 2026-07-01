// FUNC_NAME: LinkedListNode::attachToParentList
int* __thiscall LinkedListNode::attachToParentList(int* thisNode, int* parentObject) {
    int* listHead;

    // The parent object has a list head pointer at offset 0x48
    if (parentObject == 0) {
        listHead = 0;
    } else {
        listHead = parentObject + 0x48; // pointer to the list head structure (has 'first' at +0x4)
    }

    // Only relink if the node is not already in this list
    if (*thisNode != listHead) {
        // If the node is already in a list, remove it first
        if (*thisNode != 0) {
            // Removes thisNode from its current list (FUN_004daf90 is likely List::unlinkNode)
            FUN_004daf90(thisNode);
        }
        // Set this node's 'listHead' pointer (offset 0x0)
        *thisNode = listHead;

        if (listHead != 0) {
            // Insert at head: node->next = old first node, listHead->first = this node
            thisNode[1] = *(int*)(listHead + 4);       // +0x4: pointer to first node
            *(int**)(listHead + 4) = thisNode;        // update list head's first pointer
        }
    }
    return thisNode;
}