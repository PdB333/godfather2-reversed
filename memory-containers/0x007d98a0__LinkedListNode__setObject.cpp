// FUNC_NAME: LinkedListNode::setObject
// Address: 0x007d98a0
// Role: Sets the data pointer of this intrusive list node to point to the embedded node of a given object,
//       and links this node before that embedded node in a doubly-linked list.
//       The object is expected to have an intrusive list node at offset 0x48.
//       The linked list node structure (at offset 0 for this, at offset 0x48 for the object) is assumed:
//         +0x00: void* pData   (pointer to the node this node holds)
//         +0x04: LinkedListNode* pPrev (or pNext, modified by the linker)

int * __thiscall LinkedListNode::setObject(LinkedListNode *this, void *object)
{
    LinkedListNode *newNode;

    // If the object is non-null, get the address of its embedded node (offset 0x48)
    if (object == 0) {
        newNode = 0;
    } else {
        newNode = (LinkedListNode *)((char *)object + 0x48);
    }

    // Only update if the new node differs from the current one
    if (this->pData != newNode) {
        // Remove the old node from the list if it exists
        if (this->pData != 0) {
            FUN_004daf90(&this->pData);
        }

        // Set the data pointer to the new embedded node
        this->pData = newNode;

        // If the new node exists, link this node before it
        if (newNode != 0) {
            // this->next = newNode->prev
            this->pPrevOrNext = newNode->pPrevOrNext;
            // newNode->prev = this
            newNode->pPrevOrNext = this;
        }
    }

    return this;
}