// FUNC_NAME: MemoryNodePool::releaseChain
void __thiscall MemoryNodePool::releaseChain(int this, Node* node)
{
    char isFree;

    isFree = node->m_bFree; // +0x15: flag (0 = free, non-zero = occupied)
    while (isFree == '\0') {
        // Recursively release any sub-chain pointed to by node->pChild at offset +0x08
        MemoryNodePool::releaseChain(this, (Node*)node->pChild); // pChild at offset 0x08

        Node* nextNode = node->pNext; // +0x00: next pointer

        // Call virtual deallocator via vtable[1] (offset 4 from vtable pointer at this+0x04)
        void (*dealloc)(Node*, int) = (void (*)(Node*, int)) this->vtable[1];
        dealloc(node, 0x18); // deallocate 24-byte block

        node = nextNode;
        if (node != nullptr) {
            isFree = node->m_bFree;
        } else {
            break;
        }
    }
}