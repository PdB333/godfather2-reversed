// FUNC_NAME: MemoryPool::removeNodeFromList
// Function at 0x005f90d0: removes a node from a doubly linked list and returns it to the pool.
void __thiscall MemoryPool::removeNodeFromList(void* listObj, void* node, void** outResult)
{
    // listObj: pointer to a list head structure (ListHead)
    // node: pointer to the node to remove (ListNode)
    // outResult: output array of two pointers: outResult[0] = listObj, outResult[1] = node->next (for iteration)

    struct ListNode {
        ListNode* next; // +0x00
        ListNode* prev; // +0x04
        // size 0xC (12 bytes) according to the deallocation call
    };
    struct ListHead {
        // ...
        ListNode* first; // +0x18? Offset used for validation: node must not be the list's first element
    };
    struct PoolVTable {
        void (*deallocate)(void* ptr, int size); // virtual function at offset 0x04 (vtable index 1)
    };

    PoolVTable* vtable = *(PoolVTable**)this; // vtable pointer at +0x00
    ListNode* sentinel = *(ListNode**)((char*)this + 0x18); // +0x18: sentinel node that should not be removed
    int* count = (int*)((char*)this + 0x1c); // +0x1c: number of allocated nodes

    ListHead* list = (ListHead*)listObj;
    ListNode* nodeToRemove = (ListNode*)node;

    // Validation
    if (list == nullptr) {
        FUN_00b97aea(); // likely assertion failure
    }
    if (nodeToRemove == list->first) {
        FUN_00b97aea(); // cannot remove the first element of the list
    }

    ListNode* nextNode = nodeToRemove->next;

    // Only remove and deallocate if the node is not the sentinel
    if (nodeToRemove != sentinel) {
        // Standard doubly linked list removal:
        // node->prev->next = node->next
        nodeToRemove->prev->next = nextNode;
        // node->next->prev = node->prev
        nextNode->prev = nodeToRemove->prev;

        // Deallocate the node from the pool (size 0xC)
        vtable->deallocate(nodeToRemove, 0xC);
        (*count)--;
    }

    // Return the list and the next node (so caller can continue iteration)
    outResult[0] = listObj;
    outResult[1] = nextNode;
}