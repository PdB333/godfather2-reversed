// FUNC_NAME: NodeAllocator::popNodeFromList
void __thiscall NodeAllocator::popNodeFromList(int *outIterator, int *list, Node *node)
{
    int iVar1;
    // 'this' is the node allocator (passed in ECX, stored in unaff_EDI by decompiler)
    NodeAllocator *allocator = this;

    // Fail if list is null or node is the sentinel head
    if (list == 0) {
        assert();   // FUN_00b97aea
    }
    if (node == *(Node **)(list + 0x18)) {
        assert();   // FUN_00b97aea
    }

    iVar1 = node->next;   // *param_3

    // If node is not the tail sentinel (offset 0x18 in the allocator?), unlink
    if (node != (Node *)allocator->field_0x18) {
        // Relink: node->prev->next = node->next
        *(int *)node->prev = iVar1;
        // node->next->prev = node->prev
        *(int *)(node->next + 4) = node->prev;

        // Call virtual deallocate (vtable[1]) with node and size 0xC
        (allocator->vtable->deallocate)(node, 0xC);
        allocator->field_0x1c--;   // decrease count
    }

    // Output: iterator holds list and next node
    outIterator[1] = iVar1;
    *outIterator = (int)list;
}