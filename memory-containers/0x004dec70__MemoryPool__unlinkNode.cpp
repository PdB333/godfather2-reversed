// FUNC_NAME: MemoryPool::unlinkNode
void __fastcall MemoryPool::unlinkNode(void* /* unused param_1 */, MemoryPool* pool, int nodeOffset)
{
    // access per-thread memory pool data via FS segment
    int* threadData = *(int**)__readfsdword(0x2C);
    // pool data pointer at threadData+8 (byte offset, treated as char*)
    unsigned char* poolData = *(unsigned char**)(threadData + 2);

    if (nodeOffset == pool->head) // +0x14
    {
        int* node = (int*)(poolData + nodeOffset);
        int next = node[0]; // offset 0: next node index in free list
        int prev = node[1]; // offset 4: previous node index in free list
        pool->head = next;           // +0x14
        pool->tail = prev;           // +0x18

        if (next != 0)
        {
            // clear the next and prev of the new head node (located at offset 8+next)
            int* newHead = (int*)(poolData + 8 + next);
            newHead[0] = 0;
            newHead[1] = 0;
        }
    }
    else
    {
        // Node is not the head; unlink from both doubly-linked lists
        unsigned char* poolData = *(unsigned char**)(threadData + 2);
        int otherPrev = *(int*)(poolData + 8 + nodeOffset); // offset 8: index of previous node in second list
        if (otherPrev != 0)
        {
            int* dest = (int*)(poolData + otherPrev);
            int* src = (int*)(poolData + nodeOffset);
            dest[0] = src[0]; // copy first two ints (free list links) to previous node in second list
            dest[1] = src[1];
        }

        int freeListNext = *(int*)(poolData + nodeOffset); // offset 0: next index in free list
        if (freeListNext != 0)
        {
            int* dest = (int*)(poolData + freeListNext + 8); // jump to second-list fields of freeListNext
            int* src = (int*)(poolData + nodeOffset + 8);
            dest[0] = src[0]; // copy second-list links (offset 8,12) to next free list node
            dest[1] = src[1];
        }
    }
}