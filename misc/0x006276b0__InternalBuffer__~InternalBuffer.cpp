// FUNC_NAME: InternalBuffer::~InternalBuffer
void __thiscall InternalBuffer::~InternalBuffer(void) {
    // +0x10: pointer to internal allocation block (struct BufferBlock)
    BufferBlock* block = this->mBufferBlock;

    // Call start cleanup routine (maybe lock or reference count)
    FUN_006382a0();

    if (block != nullptr) {
        // Free first allocation: pointer at block+0x00, size at block+0x08
        FUN_00626f80();           // pre-free sync
        FUN_00626fd0(0x100);      // flag or size update
        FUN_00626f80();           // post sync

        // iVar2 = block->field_0x08 (count of first array elements?)
        int firstCount = block->field_0x08;
        // iVar3 = block->buf1 (pointer to first array)
        void* firstBuf = block->buf1;
        if (firstBuf != nullptr) {
            // Deallocate first array
            operator_delete(firstBuf);
            // Adjust total size counter at block+0x24
            block->totalSize -= firstCount * 4;  // subtract 4 * count
        }

        // Free second allocation: pointer at block+0x18, size at block+0x1c
        int secondCount = block->field_0x1c;  // number of bytes or elements
        void* secondBuf = block->field_0x18;  // pointer
        if (secondBuf != nullptr) {
            operator_delete(secondBuf);
            block->totalSize -= secondCount;  // subtract size directly
        }

        // Nullify second pointer and count
        block->field_0x18 = nullptr;
        block->field_0x1c = 0;
    }

    // Final cleanup routine
    FUN_00627500();

    if (block != nullptr) {
        // Deallocate the block itself
        operator_delete(block);
    }

    // Call global deallocator with no argument? Probably a destructor chain
    operator_delete();
    return;
}