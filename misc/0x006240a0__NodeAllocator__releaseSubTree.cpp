// FUNC_NAME: NodeAllocator::releaseSubTree
// Address: 0x006240a0
// Role: Recursively releases a linked tree structure of nodes. Each node has:
//   +0x00: next sibling pointer
//   +0x08: child pointer
//   +0x25: flag byte (0 = continue traversal, non-zero = stop)
// The allocator's vtable at +0x04 has a dealloc/delete function at index 1 (offset 4).
void __thiscall NodeAllocator::releaseSubTree(void* thisAllocator, int* currentNode) {
    char endFlag = *(char*)((int)currentNode + 0x25);

    while (endFlag == '\0') {
        // Recursively release the child tree (child pointer at offset 8)
        releaseSubTree((int*)currentNode[2]);

        // Get next sibling
        int* nextNode = (int*)*currentNode;

        // Call virtual deallocate function on the allocator: param1 = node, param2 = size (0x28)
        // vtable is at *(int**)((int)thisAllocator + 4), function at vtable[1]
        (**(code**)(**(int**)((int)thisAllocator + 4) + 4))(currentNode, 0x28);

        currentNode = nextNode;
        endFlag = *(char*)((int)nextNode + 0x25);
    }
}