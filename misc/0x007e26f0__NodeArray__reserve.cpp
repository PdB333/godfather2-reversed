// FUNC_NAME: NodeArray::reserve
// Address: 0x007e26f0
// Role: Resize the node array to accommodate at least newCapacity nodes.
// The array stores 8-byte nodes: [0] = object pointer, [1] = previous node pointer (back link).
// Each object has a back-pointer at offset +4 that points to its node in this array.
// When reallocating, this function updates all such back-pointers.
void __thiscall NodeArray::reserve(int *this, uint newCapacity)
{
    int *newArray;
    int oldCount;
    int *newNode;
    int *oldNode;
    uint i;

    // Only grow if newCapacity exceeds current capacity (this[2])
    if ((uint)this[2] < newCapacity) {
        // Allocate new array: newCapacity * 8 bytes (each node is 8 bytes)
        newArray = (int *)FUN_009c8e80(newCapacity * 8);
        if (this[0] != 0) {
            i = 0;
            newNode = newArray;
            if (this[1] != 0) {
                do {
                    // Pointer to current old node
                    oldNode = (int *)(this[0] + i * 8);
                    if (newNode != (int *)0x0) {
                        // Copy object pointer
                        *newNode = *oldNode;
                        // Reset back-link (temp value)
                        newNode[1] = 0;
                        if (*oldNode != 0) {
                            // Update the object's back-link to point to the new node
                            newNode[1] = *(int *)(*oldNode + 4);  // save old back-link? Actually overwrite
                            *(int **)(*oldNode + 4) = newNode;    // object->nodePointer = newNode
                        }
                    }
                    // Release the old node (likely decrements reference or removes from list)
                    if (*oldNode != 0) {
                        FUN_004daf90(oldNode);
                    }
                    i = i + 1;
                    newNode = newNode + 2;
                } while (i < (uint)this[1]);
            }
            // Free old array memory
            FUN_009c8f10(this[0]);
        }
        // Update pointer, count remains unchanged, set new capacity
        this[0] = (int)newArray;
        this[2] = newCapacity;
    }
    return;
}