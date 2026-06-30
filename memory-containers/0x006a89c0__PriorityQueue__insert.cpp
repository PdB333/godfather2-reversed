// FUNC_NAME: PriorityQueue::insert
undefined1 PriorityQueue::insert(SortedListNode* node, float key)
{
    int iVar1;
    float squaredKey;
    undefined1 result;
    undefined** vtablePtr;
    SortedListNode* tempNode;
    float tempKey;
    int tempData[4];

    squaredKey = key * key;
    tempNode = (SortedListNode*)&stack0x00000008; // Actually local_18 points to stack, but we'll handle
    result = 0;
    vtablePtr = &PTR_FUN_00d5d89c; // Global vtable for SortedListNode
    tempData[0] = 0; // next
    tempData[1] = 0; // prev
    tempData[3] = 0x20; // size or flags
    tempData[2] = 0; // key
    tempKey = squaredKey;
    // Create a temporary node with the squared key
    FUN_005fcf80(&tempNode, &vtablePtr, squaredKey); // This likely initializes tempData via tempNode
    iVar1 = tempData[0]; // tempNode->next

    // If node is not the same as tempNode and node->next != tempNode->next
    if ((node != (SortedListNode*)tempData) && (node->next != (SortedListNode*)tempData[0])) {
        // Remove node from its current list if it has a next
        if (node->next != 0) {
            FUN_004daf90(node); // Unlink or free? Probably unlink
        }
        // Insert node before tempNode
        node->next = (SortedListNode*)iVar1;
        node->prev = (SortedListNode*)((int)iVar1 + 4); // Actually *(int*)(iVar1+4) is tempNode->prev
        // But the code: param_1[1] = *(int *)(iVar1 + 4); and then *(int **)(iVar1 + 4) = param_1;
        // So node->prev = tempNode->prev; and tempNode->prev = node;
        node->prev = (SortedListNode*)(*(int*)(iVar1 + 4));
        *(int**)(iVar1 + 4) = (int*)node;
    }
    // Copy the key from tempNode to node
    node->key = *(float*)&tempData[2]; // tempData[2] is the key
    // If node has a next and the key is non-zero, set result to 1
    if ((node->next != 0) && (*(float*)&tempData[2] != 0.0f)) {
        result = 1;
    }
    vtablePtr = &PTR_FUN_00d5d89c;
    // Free the temporary node if it exists
    if (tempData[0] != 0) {
        FUN_004daf90(tempData);
    }
    return result;
}