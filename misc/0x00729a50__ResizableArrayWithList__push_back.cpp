// FUNC_NAME: ResizableArrayWithList::push_back
void __thiscall ResizableArrayWithList::push_back(int* this, Node* element) {
    int currentCount = this[1];        // this->count
    int currentCapacity = this[2];     // this->capacity

    // Grow if necessary
    if (currentCount == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        grow(newCapacity);  // reallocate to new capacity
    }

    // Pointer to new node slot (each node is 12 bytes)
    int* newSlot = (int*) (this[0] + currentCount * 0xc);
    this[1] = currentCount + 1;  // increment count

    // Copy first two fields from input element
    newSlot[0] = element->data;    // +0x00
    int ownerPtr = element->link;  // +0x04: pointer to owner object with list head at +0x04
    newSlot[1] = ownerPtr;         // +0x04: store in new node's link field

    // Initialize third field (next pointer) to 0
    newSlot[2] = 0;                // +0x08: next points to the link field of the next node (or null)

    // If owner object exists, insert this node into its singly linked list
    if (ownerPtr != 0) {
        // The owner object has a "list head" at offset 0x04 which points to the link field of the first node.
        // We store the current head into new node's next, then update head to point to this node's link field.
        newSlot[2] = *(int*)(ownerPtr + 4);      // next = old head
        *(int*)(ownerPtr + 4) = (int)(newSlot + 1); // head = &(new node's link field)
    }
    return;
}