// FUNC_NAME: 0x005e1400 MemoryPool::freeChunkTree
void __thiscall MemoryPool::freeChunkTree(int thisPtr, int* node) {
    // node structure:
    // +0x00: nextSibling (int*)
    // +0x08: child (int*)
    // +0x15: processedFlag (char, 0 = not processed yet)
    char processedFlag = *(char*)((int)node + 0x15);
    while (processedFlag == '\0') {
        // Depth-first: process child subtree first
        this->freeChunkTree(node[2]); // child at offset 0x08
        int* nextNode = (int*)*node; // next sibling at offset 0x00
        // Call virtual deallocate method (vtable + 4) with block and size 0x18
        // vtable pointer stored at thisPtr + 4
        (**(code**)(**(int**)(thisPtr + 4) + 4))(node, 0x18);
        node = nextNode;
        processedFlag = *(char*)((int)nextNode + 0x15);
    }
}