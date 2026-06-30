// FUNC_NAME: ListUtils::relinkNode
void __thiscall ListUtils::relinkNode(void* node, void* list) // replicate: node->next = node->next->prev; adjust links
{
    // node structure: offset 0 = prev, offset 4 = data, offset 8 = next, offset 0x15 = active_flag (byte)
    // list structure: offset 0x1c = head pointer (points to first node in the list)
    int* nextNode;
    int* prevPtr;
    
    // Get the next pointer of the current node (at offset 8)
    // This is actually the address of the next node
    nextNode = *(int**)((int)node + 8);    // nextNode = node->next
    
    // Overwrite node->next with the value stored at nextNode (which is the prev of the next node)
    // This effectively makes node->next point to the node pointed to by nextNode->prev
    *(int*)((int)node + 8) = *nextNode;    // node->next = nextNode->prev
    
    // Check a flag at offset 0x15 of the node pointed to by nextNode->prev
    if (*(char*)(*nextNode + 0x15) == '\0')   // if (nextNode->prev->active_flag == false)
    {
        // If the flag is false, set nextNode->prev->data to the current node
        *(int*)(*nextNode + 4) = (int)node;   // (nextNode->prev)->data = node
    }
    
    // Copy current node's data to the next node's data field
    // nextNode[1] is the int at nextNode+4 (i.e., nextNode->data)
    // *(int*)(node+4) is the current node's data
    *(int*)(nextNode + 1) = *(int*)((int)node + 4);   // nextNode->data = node->data
    
    // Check if the current node is the tail of the list (head->data == node)
    // head pointer is at list+0x1c; head->data is at head+4
    if ((int)node == *(int*)(*(int*)((int)list + 0x1c) + 4))   // if (node == list->head->data)
    {
        // Update the tail of the list: head->data points to nextNode
        *(int**)(*(int*)((int)list + 0x1c) + 4) = nextNode;  // list->head->data = nextNode
        // Set nextNode->prev to current node (making it the new tail's prev)
        *nextNode = (int)node;
        // Set node->data to nextNode (link back)
        *(int**)((int)node + 4) = nextNode;
        return;
    }
    
    // Get the prev pointer of the current node (at offset 4)
    prevPtr = *(int**)((int)node + 4);   // prevPtr = node->data (actually a pointer to previous node)
    
    // Check if current node is the head (node == node->data->prev?) Actually compare with prevPtr[0]
    if ((int)node == *prevPtr)   // if (node == prevPtr->prev)   // ??? compare node with prev of the node pointed by prevPtr
    {
        // Relink head: prevPtr->prev = nextNode
        *prevPtr = (int)nextNode;
        // Set nextNode->prev to current node
        *nextNode = (int)node;
        // Update node->data to nextNode
        *(int**)((int)node + 4) = nextNode;
        return;
    }
    
    // Otherwise, operate on some intermediate node
    // prevPtr[2] is the third int of the node pointed by prevPtr (offset 8, which is its next pointer)
    *(int*)(prevPtr + 2) = (int)nextNode;   // prevPtr->next = nextNode
    *nextNode = (int)node;                  // nextNode->prev = node
    *(int**)((int)node + 4) = nextNode;     // node->data = nextNode
    return;
}