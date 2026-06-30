// FUNC_NAME: BufferManager::destructor
void __thiscall BufferManager::destructor(void)
{
    char tmpBuffer[12]; // Stack-allocated temporary buffer

    // Initialize temp buffer from the existing data pointer (internal copy/validation)
    FUN_00623210(tmpBuffer, this, **(void***)(this + 0x1c), this, *(void**)(this + 0x1c));

    // Call virtual deallocation on the allocator stored at +0x04
    // Allocator vtable entry at offset 0x04 (index 1) takes (bufferPointer, size=0x18)
    Allocator* alloc = *(Allocator**)(this + 4);
    alloc->deallocate(*(void**)(this + 0x1c), 0x18);

    // Clear the managed buffer fields
    *(void**)(this + 0x1c) = 0;
    *(void**)(this + 0x20) = 0;
}