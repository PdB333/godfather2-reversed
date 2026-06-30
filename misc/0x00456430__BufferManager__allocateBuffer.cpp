// FUNC_NAME: BufferManager::allocateBuffer
struct BufferBlock {
    void* vtable;        // +0x00
    uint32_t flags;      // +0x04
    uint32_t relativeOffset; // +0x08 – relative offset to data, adjusted to absolute later
    void* dataStart;     // +0x0C – points to actual data area
};

// Class with freeListHead at +0x14 and currentBlock at +0x1c
class BufferManager {
public:
    BufferBlock* freeListHead;  // +0x14
    BufferBlock* currentBlock;  // +0x1c

    // Retrieves the current free buffer head, initializes it, and returns it
    BufferBlock* allocateBuffer() {
        BufferBlock* block = this->freeListHead;
        this->currentBlock = block;
        if (block != nullptr) {
            block->flags = 0;
            block->vtable = (void*)&PTR_FUN_00e36670; // vtable for this buffer type
            if (block->relativeOffset != 0) {
                // Convert relative offset to absolute by adding the block's own base address
                block->relativeOffset = (uint32_t)block + block->relativeOffset;
            }
            // Data area begins 16 bytes after the (now absolute) pointer
            block->dataStart = (void*)(block->relativeOffset + 0x10);
            return block;
        }
        return nullptr;
    }
};