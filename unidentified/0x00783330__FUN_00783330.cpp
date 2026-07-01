// FUNC_NAME: SomeContainer::removeAt
void __thiscall SomeContainer::removeAt(int *this, unsigned int index)
{
    int *currentNode;
    int nextObjectPtr;
    unsigned int i;

    // Shift elements left from index to size-2
    if (index < this[1] - 1U) {
        for (i = index; i < this[1] - 1U; i++) {
            currentNode = (int *)(*this + i * 8); // +0x00: base pointer, each node is 8 bytes
            // Check if current node is not the same as next node (always true)
            if (currentNode != currentNode + 2) {
                nextObjectPtr = currentNode[2]; // next node's object pointer
                // If current object differs from next object
                if (*currentNode != nextObjectPtr) {
                    // Destroy current object if non-null
                    if (*currentNode != 0) {
                        FUN_004daf90(currentNode);
                    }
                    // Copy next object pointer into current
                    *currentNode = nextObjectPtr;
                    // Update linked list: current's next pointer becomes next object's next pointer
                    if (nextObjectPtr != 0) {
                        currentNode[1] = *(int *)(nextObjectPtr + 4); // +0x04: object's next pointer
                        // Make next object's next point back to current node
                        *(int **)(nextObjectPtr + 4) = currentNode;
                    }
                }
            }
        }
    }
    // Decrement size
    this[1] = this[1] - 1;
    // If the last element (now at new size) has a non-null object, destroy it
    if (*(int *)(*this + this[1] * 8) != 0) {
        FUN_004daf90();
    }
}