// 0x006bd130: ObjectRefList::add
void __thiscall ObjectRefList::add(void* object)
{
    // Check if array is full; if so, grow by doubling capacity (minimum 1)
    if (count == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        growCapacity(newCapacity); // FUN_006bc970 – reallocates the nodes array
    }

    // Get pointer to the new node at the end of the array
    Node* newNode = &nodes[count];
    count++;

    // Store the object pointer in the node's data field
    newNode->data = object;
    newNode->next = nullptr; // default: not linked

    // If the object is non-null, link this node into the object's own list of references.
    // The object is assumed to have a pointer at offset +0x04 that points to the first node
    // referencing it (a single-linked list). The new node becomes the new head.
    if (object != nullptr)
    {
        Node* oldHead = *(Node**)((char*)object + 4);
        newNode->next = oldHead;          // new node points to old head
        *(Node**)((char*)object + 4) = newNode; // object now points to new head
    }
}