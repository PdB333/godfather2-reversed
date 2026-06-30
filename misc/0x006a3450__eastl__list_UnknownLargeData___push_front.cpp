// FUNC_NAME: eastl::list<UnknownLargeData>::push_front
// Allocates a new node (size 0x45C) and inserts it at the front of a doubly linked list with sentinel.
// param_1: this pointer (sentinel node, offset 0 = prev, offset 4 = next)
// param_2: pointer to source data (copied into node data area, size 0x454 = 0x115 * 4)
void __thiscall eastl::list<UnknownLargeData>::push_front(void *thisPtr, int *srcData)
{
    // Allocate node: 8 bytes for prev/next pointers + 0x454 bytes of data
    int *newNode = (int *)FUN_0068ab90(0x45c, "EASTL",
                                       0, 0,
                                       "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
                                       0xe9);
    if (newNode == nullptr) {
        return; // allocation failure (original code checks (node+2) != 0 which is always true for non-null)
    }

    // Copy data (0x115 ints = 0x454 bytes) into node's data area starting at offset 8
    int *dest = newNode + 2;
    for (int i = 0x115; i != 0; --i) {
        *dest++ = *srcData++;
    }

    // Doubly linked list insertion at front
    // newNode->prev = sentinel
    *newNode = (int)thisPtr;
    // newNode->next = sentinel->next
    newNode[1] = *(int *)((char *)thisPtr + 4);
    // sentinel->next->prev = newNode
    **(int **)((char *)thisPtr + 4) = (int)newNode;
    // sentinel->next = newNode
    *(int **)((char *)thisPtr + 4) = newNode;
}