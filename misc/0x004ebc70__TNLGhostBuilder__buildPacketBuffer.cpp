// FUNC_NAME: TNLGhostBuilder::buildPacketBuffer
void TNLGhostBuilder::buildPacketBuffer() {
    // Linked list of ghost chunks, each with vtable and flags (offset +0xc)
    struct GhostChunk {
        void* vtable;          // +0x00
        GhostChunk* next;      // +0x04
        int unknown8;          // +0x08
        int flags;             // +0x0C (non-zero means include in packet)
    };

    GhostChunk* chunk = this->head;
    int totalSize = 0;

    if (chunk == nullptr) return;

    // First pass: compute total buffer size (16-byte header + aligned data)
    do {
        if (chunk->flags != 0) {
            int dataSize = ((int (*)())chunk->vtable)();  // vtable[0]: returns serialized size
            totalSize += 0x10 + ((dataSize + 0xF) & ~0xF);
        }
        chunk = chunk->next;
    } while (chunk != nullptr);

    if (totalSize == 0) return;

    // Allocate aligned buffer
    Allocator* alloc = getDefaultAllocator();
    struct AllocInfo {
        int type;       // = 2 (likely heap type)
        int alignment;  // = 0x10
        void* result;   // output pointer
    } info = {2, 0x10, nullptr};

    int* buffer = (int*)alloc->allocate(totalSize, &info);
    if (buffer == nullptr) return;

    // Second pass: serialize chunks into buffer
    int* writePtr = buffer;
    chunk = this->head;
    int* lastChunkHeader = nullptr;

    do {
        if (chunk->flags != 0) {
            // Copy vtable and next pointers (first 8 bytes) into buffer header
            *(int*)writePtr = *(int*)chunk;
            *(int*)(writePtr + 2) = *(int*)((int)chunk + 4);

            // Call serialization method vtable[1] on the buffer copy
            ((void (*)())(*(int*)(*(int*)writePtr + 4)))();

            // Retrieve data size again (vtable[0])
            int dataSize = ((int (*)())(*(int*)writePtr))();

            // Advance write pointer: header (16 bytes) + aligned data
            int* nextWrite = writePtr + ((dataSize + 0xF) >> 4) + 1;
            writePtr[2] = (int)nextWrite; // link to next chunk header
            writePtr[3] = 0;

            lastChunkHeader = writePtr;
            writePtr = nextWrite;
        }
        chunk = chunk->next;
    } while (chunk != nullptr);

    // Terminate the list
    if (lastChunkHeader != nullptr) {
        lastChunkHeader[2] = 0;
    }
}