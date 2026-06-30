// FUNC_NAME: ResourceRef::operator=
// Function at 0x004d9ff0: Copy assignment operator for ResourceRef class
// Structure contains 30 bytes: 3x8 bytes, 1x4 bytes, 1x2 bytes (offsets 0,8,16,24,28)
// At offset 4 (pointer) to a ref-counted block with refcount at +0x20
void __thiscall ResourceRef::operator=(const ResourceRef& other)
{
    // If assigning to self, do nothing
    if (this == &other) {
        return;
    }

    // Release current reference if any
    RefBlock* currentBlock = *(RefBlock**)((char*)this + 4);
    if (currentBlock != nullptr) {
        if (*(int*)((char*)currentBlock + 0x20) != 0) {
            releaseRef(1); // Decrement refcount, possibly free if zero
        }
        freeBlock(currentBlock);
    }
    *(RefBlock**)((char*)this + 4) = nullptr;

    // Copy the raw structure data (30 bytes)
    *(uint64_t*)((char*)this + 0) = *(uint64_t*)((char*)&other + 0);
    *(uint64_t*)((char*)this + 8) = *(uint64_t*)((char*)&other + 8);
    *(uint64_t*)((char*)this + 16) = *(uint64_t*)((char*)&other + 16);
    *(uint32_t*)((char*)this + 24) = *(uint32_t*)((char*)&other + 24);
    *(uint16_t*)((char*)this + 28) = *(uint16_t*)((char*)&other + 28);

    // If the source has a valid block, acquire a new reference (clone)
    RefBlock* srcBlock = *(RefBlock**)((char*)&other + 4);
    if (srcBlock != nullptr) {
        RefBlock* newBlock = (RefBlock*)allocateBlock(sizeof(RefBlock)); // 0x24 bytes
        if (newBlock != nullptr) {
            *(RefBlock**)((char*)this + 4) = cloneBlock(srcBlock);
            return;
        }
        *(RefBlock**)((char*)this + 4) = nullptr;
        // Note: If allocation fails, the pointer remains null (leak of copied struct? but consistent)
    }
    return;
}