// FUNC_NAME: LinkedList::insertNode
void __fastcall LinkedList::insertNode(int this, int pObject)
{
    // Call virtual function at vtable[0x28/4] = vtable[10] with argument 0x10
    (*(void (**)(int))(*(int *)(this + 0x58) + 0x28))(0x10);

    // Pointer to head of linked list at this+0x214
    int* pListHead = (int*)(this + 0x214);
    // Node is embedded at offset 0x48 in the passed object
    int* pNode;
    if (pObject == 0) {
        pNode = 0;
    } else {
        pNode = (int*)(pObject + 0x48);
    }

    // Only modify if the head is not already pointing to this node
    if (*pListHead != (int)pNode) {
        // If there was an existing head, detach it (probably back-link removal)
        if (*pListHead != 0) {
            FUN_004daf90(pListHead); // remove old head from list
        }
        // Set head to new node
        *pListHead = (int)pNode;
        if (pNode != 0) {
            // Store the old "next" pointer from the new node into this->0x218
            *(int*)(this + 0x218) = *(int*)((int)pNode + 4); // +0x218
            // Set new node's "next" pointer (offset +4) to point back to the head pointer location
            *(int**)((int)pNode + 4) = pListHead; // pNode->next = &head
        }
    }
}