// FUNC_NAME: LinkedListArray::reserveCapacity
// Address: 0x00729630
// Role: Increase capacity of a contiguous linked list array. Reallocates buffer and relinks nodes.
// Nodes are 12 bytes: data (0), prevNode (4), nextNode (8). prevNode points to the predecessor node.

void __thiscall LinkedListArray::reserveCapacity(int *this, uint newCapacity)
{
    if (this[2] < newCapacity) {
        // Allocate new buffer: newCapacity * 12 bytes
        int newBuffer = allocator::allocate(newCapacity * 12);

        if (this[0] != 0) {
            uint i = 0;
            if (this[1] != 0) {
                // Iterate over existing nodes, copy to new buffer
                int *newNodePrev = (int *)(newBuffer + 4); // points to prev field of first node
                do {
                    // Compute pointer to corresponding old node
                    int *oldNodeData = (int *)this[0];
                    // piVar3 = oldNode + (newNodePrev - newBuffer - 4)? Actually simplifies to oldNode
                    int *oldNode = (int *)((int)newNodePrev + this[0] - newBuffer - 4);
                    // Actually piVar3 = oldNode, because (newNodePrev - newBuffer - 4) = 0

                    // Copy data and prevNode from old node to new node
                    newNodePrev[-1] = oldNode[0];   // data
                    int *oldPrevNode = (int *)oldNode[1]; // previous node pointer
                    *newNodePrev = (int)oldPrevNode; // prevNode
                    newNodePrev[1] = 0;               // nextNode initially null

                    if (oldPrevNode != 0) {
                        // Insert new node after its predecessor in the linked list
                        newNodePrev[1] = oldPrevNode[1];  // new node's next = predecessor's next
                        oldPrevNode[1] = (int)newNodePrev;  // predecessor's next = new node
                    }

                    // Release the old previous node reference (e.g., decrement refcount)
                    if (oldNode[1] != 0) {
                        nodeRelease(oldNode + 1);
                    }

                    i++;
                    newNodePrev += 3; // advance by 12 bytes
                } while (i < this[1]);
            }
            // Free old buffer
            allocator::free(this[0]);
        }

        // Update buffer, capacity
        this[0] = newBuffer;
        this[2] = newCapacity;
    }
    return;
}