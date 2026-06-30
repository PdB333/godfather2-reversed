// FUNC_NAME: ListNodeManager::detachNode

void __thiscall ListNodeManager::detachNode(void *thisPtr, void *nodeOwner)
{
    // Local helper object with a vtable (likely scoped guard or iterator)
    LocalHelper helper;
    helper.vtable = &VTable_00e31e2c;  // vtable for helper class

    // Determine node pointer: if nodeOwner is non-null, node is at offset 0x48
    ListNode *node = (nodeOwner != 0) ? (ListNode *)((char *)nodeOwner + 0x48) : 0;

    int savedNext = 0;
    if (node != 0) {
        savedNext = node->next;            // save next pointer (+0x04)
        node->next = (int *)&node;         // temporarily redirect next to itself (detach?)
    }

    // Get list head from this instance at offset 100 (0x64)
    int *listHead = *(int **)((char *)thisPtr + 100);
    int zero = 0;
    FUN_00408a00(&listHead, 0);            // likely clears the list head or performs some update

    if (node != 0) {
        FUN_004daf90(&node);               // cleanup/destroy the node
    }

    return;
}