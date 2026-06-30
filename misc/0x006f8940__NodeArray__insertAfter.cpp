// FUNC_NAME: NodeArray::insertAfter

void __thiscall NodeArray::insertAfter(int* this, int* pInsertNode)
{
    // this: pointer to NodeArray structure
    // +0x00: m_nodes (pointer to array of Node elements, each 0xC bytes)
    // +0x04: m_size (current count)
    // +0x08: m_capacity (max count before resize)
    // pInsertNode: pointer to a structure with:
    //   +0x00: m_link (pointer to an existing node to insert after)
    //   +0x08: m_byte (a byte value to store)
    //   +0x04: unused

    int currentSize = this[1];       // m_size
    int capacity = this[2];         // m_capacity

    // Resize if full
    if (currentSize == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // External resize function (assumed to reallocate m_nodes and update capacity)
        FUN_006f81c0(newCapacity);
    }

    // Get pointer to the new node slot at the end of the array
    int* base = (int*)this[0];       // m_nodes
    int* newNode = base + this[1] * 3; // each node is 3 ints (12 bytes)
    this[1] = this[1] + 1;           // increment size

    if (newNode != (int*)0x0) {
        // Copy the link pointer from the input
        int* linkTarget = (int*)*pInsertNode;
        *newNode = (int)linkTarget;  // newNode->m_link = linkTarget

        // Initialize next pointer to 0
        newNode[1] = 0;              // newNode->m_next = 0

        // If the linkTarget is not null, insert newNode after it in a linked list
        if (linkTarget != (int*)0x0) {
            // newNode->m_next = linkTarget->m_next
            newNode[1] = *(int*)(linkTarget + 1);
            // linkTarget->m_next = newNode
            *(int**)(linkTarget + 1) = newNode;
        }

        // Copy the byte field from the input
        *(char*)(newNode + 2) = *(char*)(pInsertNode + 2);  // newNode->m_byte = pInsertNode->m_byte
    }
    return;
}