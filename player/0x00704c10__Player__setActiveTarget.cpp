// FUNC_NAME: Player::setActiveTarget
void __thiscall Player::setActiveTarget(Object* targetObj) {
    // +0x24bc: pointer to head of the singly-linked list of target nodes (each node embedded in an object at offset 0x48)
    int** ppHead = (int**)(this + 0x24bc);
    
    // Get the embedded list node from the target object (offset 0x48)
    int* newNode = (targetObj != 0) ? (int*)((int)targetObj + 0x48) : 0;
    
    if (*ppHead != newNode) {
        // Remove the current head node from the list before replacing
        if (*ppHead != 0) {
            unlinkNode(ppHead); // FUN_004daf90 – removes the node pointed to by *ppHead from the intrusive list
        }
        
        *ppHead = newNode;
        
        if (newNode != 0) {
            // +0x24c0: stores the target object's previous "next" pointer (saved for restoration during removal)
            *(int*)(this + 0x24c0) = *(int*)(newNode + 4);
            // +4: the node's "next" pointer is repurposed to point to the head pointer itself (enables O(1) removal)
            *(int**)(newNode + 4) = ppHead;
        }
    }
}