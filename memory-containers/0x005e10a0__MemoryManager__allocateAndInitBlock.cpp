// FUNC_NAME: MemoryManager::allocateAndInitBlock
void __fastcall MemoryManager::allocateAndInitBlock(MemoryManager* this)
{
    // offset +0x04: pointer to allocator object (vtable)
    // offset +0x08: existing buffer (placement hint) or null

    uint* placementHint = *(uint**)(this + 8);
    uint stackBuffer[3]; // temporary fallback when no existing buffer

    if (placementHint == nullptr)
    {
        stackBuffer[0] = 0;
        stackBuffer[1] = 0;
        stackBuffer[2] = 0;
        placementHint = stackBuffer;
    }

    // Call virtual allocator function: size 0x18, placement hint
    uint* newBlock = (*(uint* (*)(int, uint*))(*((uint**)(this + 4))))(0x18, placementHint);

    // Initialize allocated block: first three uint32 to 0
    if (newBlock != nullptr)
    {
        newBlock[0] = 0; // +0x00
        newBlock[1] = 0; // +0x04
        newBlock[2] = 0; // +0x08
    }

    // Set flags at offsets
    *(uint8*)(newBlock + 5)           = 1;  // +0x14: set to 1
    *(uint8*)((uint8*)newBlock + 0x15) = 0;  // +0x15: set to 0

    return;
}