// FUNC_NAME: ComponentList::add
void __thiscall ComponentList::add(void *obj)
{
    // this +0x00: buffer (array of 8-byte nodes)
    // this +0x04: size (number of nodes)
    // this +0x08: capacity (allocated node count)
    int *thisPtr = reinterpret_cast<int*>(this);
    int currentSize = thisPtr[1];      // +0x04
    int currentCapacity = thisPtr[2];  // +0x08

    // Grow the buffer if needed (double or start at 1)
    if (currentSize == currentCapacity)
    {
        int newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        FUN_00823ce0(newCapacity);  // reallocate buffer to hold newCapacity nodes
    }

    // Calculate address of the new node at buffer[currentSize]
    // Each node is 8 bytes: [void* object, Node* next]
    Node *newNode = reinterpret_cast<Node*>(
        reinterpret_cast<uint8_t*>(thisPtr[0]) + currentSize * 8
    );
    thisPtr[1] = currentSize + 1;  // increment size

    // Initialize the node: set object pointer and clear next
    newNode->object = obj;
    newNode->next = nullptr;

    // If the object is non-null, prepend this node to the object's linked list
    // Assumes the object has a field at offset +0x04 that holds the head of a Node list
    if (obj != nullptr)
    {
        // obj->componentListHead (offset +0x04) becomes newNode
        // newNode->next becomes obj's old head
        newNode->next = *reinterpret_cast<Node**>(reinterpret_cast<uint8_t*>(obj) + 4);
        *reinterpret_cast<Node**>(reinterpret_cast<uint8_t*>(obj) + 4) = newNode;
    }
}