// FUNC_NAME: Node::attachToTailList
// 008dd630: Attaches this node to the tail of a doubly-linked list stored in a container object.
// Node structure: +0x00 = pointer to list container's head field location
//                 +0x04 = pointer to previous node in list
// Container's list control block (at +0x48 from container base): +0x00 = head pointer, +0x04 = tail pointer

int* __thiscall Node::attachToTailList(int* container) {
    // Shift to the list control block within the container
    int* listHeadField = (container != nullptr) ? (container + 0x48 / sizeof(int)) : nullptr; // +0x48

    // Only reattach if the container changes
    if (this->containerField != listHeadField) {
        // Remove from previous list if any
        if (this->containerField != nullptr) {
            removeFromList((int*)this); // FUN_004daf90 – detaches node from its previous container
        }
        this->containerField = listHeadField;

        if (listHeadField != nullptr) {
            // Link at tail: store current tail as prev, then set container's tail to this node
            this->prevNode = reinterpret_cast<Node*>(listHeadField[1]); // +0x04 in control block = tail pointer
            listHeadField[1] = reinterpret_cast<int>(this);             // update tail
        }
    }
    return this;
}