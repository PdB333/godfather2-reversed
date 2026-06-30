// FUNC_NAME: DoublyLinkedArray::insert
int * DoublyLinkedArray::insert(uint index) {
    int *nodePtr;
    int oldKey;
    uint oldCount;
    int *newNodePtr;
    int newCapacity;
    int shiftCount;

    newCapacity = this->capacity;
    if (this->itemCount == newCapacity) {
        // Double capacity, minimum 1
        if (newCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity *= 2;
        }
        this->grow(newCapacity);
    }

    oldCount = this->itemCount;
    if (index != oldCount) {
        // Inserting not at end: need to shift elements and relink
        nodePtr = (int *)(this->buffer + oldCount * 12);
        if (nodePtr != nullptr) {
            // Remove the last node from its linked list position and move it
            // to the slot that will become the new node (after shifting)
            oldKey = nodePtr[-3]; // data pointer from previous node
            nodePtr[0] = oldKey; // assign to current slot
            nodePtr[1] = 0; // clear next pointer
            if (oldKey != 0) {
                nodePtr[1] = *(int *)(oldKey + 4); // set next to oldKey's next
                *(int **)(oldKey + 4) = nodePtr; // update previous node's next
            }
            nodePtr[2] = nodePtr[-1]; // set prev to previous node's prev
        }
        // Shift all elements from position index to oldCount-1 to the right by one
        oldCount = this->itemCount - 1;
        if (index < oldCount) {
            shiftCount = oldCount - index;
            newCapacity = (int)(oldCount * 12);
            do {
                nodePtr = (int *)(newCapacity + this->buffer);
                if (nodePtr != nodePtr - 3) {
                    oldKey = nodePtr[-3];
                    if (nodePtr[0] != oldKey) {
                        if (nodePtr[0] != 0) {
                            this->destroyNode(nodePtr); // destructor
                        }
                        nodePtr[0] = oldKey;
                        if (oldKey != 0) {
                            nodePtr[1] = *(int *)(oldKey + 4);
                            *(int **)(oldKey + 4) = nodePtr;
                        }
                    }
                }
                newCapacity -= 12;
                shiftCount--;
                nodePtr[2] = nodePtr[-1]; // copy previous node's prev
            } while (shiftCount != 0);
        }
        this->itemCount++;
        // Clear the slot at index (where new node will go)
        newCapacity = index * 12;
        if (*(int *)(this->buffer + newCapacity) != 0) {
            this->destroyNode(this->buffer + newCapacity);
        }
        newNodePtr = (int *)(this->buffer + newCapacity);
        if (newNodePtr != nullptr) {
            newNodePtr[0] = 0;
            newNodePtr[1] = 0;
        }
        return (int *)(this->buffer + newCapacity);
    }

    // Inserting at the end: just clear and return the new slot
    newNodePtr = (int *)(this->buffer + oldCount * 12);
    if (newNodePtr != nullptr) {
        newNodePtr[0] = 0;
        newNodePtr[1] = 0;
    }
    this->itemCount++;
    return (int *)(this->buffer + oldCount * 12);
}