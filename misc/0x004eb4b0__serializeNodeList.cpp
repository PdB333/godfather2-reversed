// FUNC_NAME: serializeNodeList
void serializeNodeList(int *outPtr) {
    uint nodeCount = 0;
    int *allocatorPtr;
    uint *node;
    uint *dest;
    int i;
    uint dataSize;

    // If outPtr points to an existing allocation, free it first using a vtable call
    if (*outPtr != 0) {
        allocatorPtr = (int *)getMemoryAllocator(); // FUN_009c8f80 - get allocator singleton
        (*(code **)(*allocatorPtr + 4))(*outPtr, 0); // virtual free
        *outPtr = 0;
    }

    // First pass: calculate total size needed for the flat buffer
    node = in_EAX; // in_EAX is the head of the linked list passed in register, likely __fastcall convention
    uint totalSize = 1; // space for node count at start (1 word)
    if (node != nullptr) {
        do {
            if (node[2] != 0) { // node is active
                // +1 for the header word (flags/size), + (node[1] + 3) / 4 for data
                totalSize += 1 + ((node[1] + 3) >> 2);
            }
            node = (uint *)node[3]; // next node
        } while (node != nullptr);
    }

    // Allocate buffer via allocator
    allocatorPtr = (int *)getMemoryAllocator();
    int allocFlags[2]; // stack locals for allocation parameters
    allocFlags[0] = 2; // alignment? 
    allocFlags[1] = 4; // type?
    int *allocResult = (int *)0;
    int buffer = (**(code **)*allocatorPtr)(totalSize * 4, &allocFlags); // allocate memory for totalSize words
    *outPtr = buffer;

    if (buffer != 0) {
        dest = (uint *)(buffer + 4); // skip first word (will store count later)
        node = in_EAX;
        while (node != nullptr) {
            if (node[2] != 0) {
                dataSize = node[1];
                // Write header: lower 24 bits from node[0] + size in upper 8 bits
                *dest = (node[0] & 0xFFFFFF) | (dataSize << 24);
                // Copy the data payload (FUN_004eb3f0 does a memcpy-like operation)
                FUN_004eb3f0(dest + 1); // copies node[1] bytes from the source (hidden in the linked list?)
                // Advance destination by header + data (padded to word boundary)
                dest = dest + 1 + ((dataSize + 3) >> 2);
                nodeCount++;
            }
            node = (uint *)node[3];
        }
        // Store node count at beginning of buffer
        *(int *)*outPtr = nodeCount;
    }
}