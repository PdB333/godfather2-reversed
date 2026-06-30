// FUNC_NAME: NodeList::allocateAndInitFirstNode
void NodeList::allocateAndInitFirstNode(int nodeIndex) // nodeIndex in ESI
{
    // Allocation info structure (likely flags for memory allocator)
    struct AllocInfo {
        int field0; // 2
        int field4; // 0x10
        int field8; // 0
    };
    AllocInfo allocInfo = {2, 0x10, 0};

    // Function pointer from global DAT_01194538 (likely a memory allocator)
    typedef void* (*AllocFunc)(size_t size, AllocInfo* info);
    AllocFunc allocFunc = *(AllocFunc*)(*(int*)0x01194538);

    // Allocate (nodeIndex+1) * 16 bytes (each node is 16 bytes)
    short* buffer = (short*)allocFunc((nodeIndex + 1) * 0x10, &allocInfo);
    if (buffer == nullptr) return;

    // Initialize the first node (at offset 0)
    // Node layout (16 bytes):
    // +0x00: short nodeIndex (the index of this node)
    // +0x02: short flags (0)
    // +0x04: padding (4 bytes, uninitialized)
    // +0x08: pointer to next node (points to offset 0x10, i.e., the second node)
    // +0x0C: padding (4 bytes, uninitialized)
    *(short**)(buffer + 4) = buffer + 8; // next pointer at offset 8 points to offset 16 (second node)
    buffer[1] = 0;                       // flags = 0
    buffer[0] = (short)nodeIndex;        // store the node index
}