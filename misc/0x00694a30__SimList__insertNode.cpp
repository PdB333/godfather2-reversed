// FUNC_NAME: SimList::insertNode
void __thiscall SimList::insertNode(int nodePtr) {
    // nodePtr is the node to be inserted/reordered
    // nodePtr +0x8: pointer to a SimLink structure (link)
    // SimLink has fields: prev (offset 0), next (offset 4)
    int* link = *(int**)(nodePtr + 8);
    // Update node's link to point to the previous node's link? (dereference link->prev)
    *(int*)(nodePtr + 8) = *link;  // node->link = link->prev (the old head of the link?)
    
    // Check a flag in the node that was previously at the link position (node pointed to by link->prev)
    if (*(char*)(*link + 0x29) == '\0') {
        // Set that node's next (offset 4) to current node
        *(int*)(*link + 4) = nodePtr;
    }
    // Set link's next to the node's previous next
    link[1] = *(int*)(nodePtr + 4);  // link->next = node->next
    
    // Special cases for tail or head of the list
    int* headPtr = *(int**)(this + 4);  // this+4 points to a sentinel/head node
    if (nodePtr == *(int*)(headPtr + 4)) {  // if node equals sentinel's next (i.e., node is the tail)
        // Update sentinel's next to point to the link
        *(int**)(headPtr + 4) = link;
        *link = nodePtr;           // link->prev = node
        *(int**)(nodePtr + 4) = link; // node->next = link
        return;
    }
    
    int* nextNode = *(int**)(nodePtr + 4);  // node's next pointer
    if (nodePtr == *nextNode) {  // if node equals next node's prev (circular list)
        *nextNode = (int)link;   // nextNode->prev = link
        *link = nodePtr;         // link->prev = node
        *(int**)(nodePtr + 4) = link; // node->next = link
        return;
    }
    
    // General case: detach and reattach
    nextNode[2] = (int)link;     // nextNode->link (offset 8) = link
    *link = nodePtr;             // link->prev = node
    *(int**)(nodePtr + 4) = link; // node->next = link
}