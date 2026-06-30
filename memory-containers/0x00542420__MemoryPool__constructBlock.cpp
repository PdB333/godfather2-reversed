// FUNC_NAME: MemoryPool::constructBlock
void __fastcall MemoryPool::constructBlock(int this) {
    // Call base constructor at this - 4 (likely a base subobject or header)
    ConstructBaseObject(this - 4);

    int nextOffset = (this == 4) ? 0 : (this + 4); // If block size is 4, no additional allocation
    ConstructDerivedObject(nextOffset);

    GlobalInit(); // Final global initialization

    // Zero out field at offset +0xC (e.g., reference count or flag)
    *reinterpret_cast<int*>(this + 0xC) = 0;
}