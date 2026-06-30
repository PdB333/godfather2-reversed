// FUNC_NAME: ObjectNode::attachToContainer
// Reconstructed from 0x006f7ef0 - inserts this node into a linked list managed by a container.

int* __thiscall ObjectNode::attachToContainer(ObjectNode* thisNode, int container)
{
    int* listHead;
    
    // Compute address of list head node: container + 0x48 (offset of embedded list head)
    if (container == 0) {
        listHead = 0;
    } else {
        listHead = (int*)(container + 0x48);
    }
    
    // Set previous pointer of this node to the list head
    thisNode[0] = (int)listHead;
    // Initialize next pointer to null
    thisNode[1] = 0;
    
    // If list head exists, insert this node after the head
    if (listHead != 0) {
        // Set thisNode->next = listHead->next (the old first element)
        thisNode[1] = *(int*)(listHead + 1); // listHead[1] is the next pointer
        // Update listHead->next to point to this node (new first element)
        *(int**)(listHead + 1) = thisNode;
    }
    
    // Clear the byte flag at offset +2 of this node
    *((unsigned char*)thisNode + 2) = 0;
    
    // Check a deep flag in the container: 
    // container + 0x2124 -> pointer -> +0x20 -> uint32, test bit 7
    int* somePtr = *(int**)(container + 0x2124);
    if (somePtr != 0) {
        if ((*(unsigned int*)((char*)somePtr + 0x20) >> 7) & 1) {
            // Set flag at thisNode+2 to 1 and call a helper function
            *((unsigned char*)thisNode + 2) = 1;
            FUN_0071ed70(0);
        }
    }
    
    return thisNode;
}