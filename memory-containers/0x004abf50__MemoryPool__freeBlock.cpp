// FUNC_NAME: MemoryPool::freeBlock
void __thiscall MemoryPool::freeBlock(uint* block)
{
    uint* base = this->base; // +0x00
    if (block != nullptr && base != nullptr)
    {
        // +0x1C: errorHandler object
        if (this->errorHandler != nullptr &&
            (block < base || (this->size + (int)base) <= block)) // +0x04
        {
            // Out-of-range pointer: notify error handler (virtual call at offset 8)
            (**(code**)(*(int*)this->errorHandler + 8))();
            return;
        }
        // Standard free: insert block at head of free list, increment free count
        *block = this->freeHead;              // +0x08: freeHead -> store as next link
        this->freeCount++;                    // +0x14: freeCount
        this->freeHead = block;               // +0x08: update head to this block
    }
}