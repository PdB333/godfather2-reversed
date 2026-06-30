// FUNC_NAME: CMemoryManager::destroyNodeRecursive
void __thiscall CMemoryManager::destroyNodeRecursive(int* this, int* node)
{
    char isPending;
    int* nextNode;

    isPending = *(char*)((int)node + 0x15);
    while (isPending == '\0') {
        // Recurse into child (node[2] is offset +8)
        destroyNodeRecursive(this, (int*)*(int*)((int)node + 8));

        // Save next sibling before potentially freeing current node
        nextNode = (int*)*node;

        // Call virtual method at vtable offset 4 (likely memory deallocator)
        // Passing node pointer and size 0x18 (24 bytes) for allocation
        (**(code**)(**(int**)((int)this + 4) + 4))(node, 0x18);

        // Move to next sibling
        node = nextNode;

        isPending = *(char*)((int)node + 0x15);
    }
}