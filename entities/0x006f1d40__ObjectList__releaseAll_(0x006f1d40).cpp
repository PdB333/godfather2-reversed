// FUNC_NAME: ObjectList::releaseAll (0x006f1d40)

class ObjectList {
public:
    // Structure layout:
    // +0x00: head (pointer to first node)
    // +0x04: current (iterator, used during traversal)
    // +0x08: count (number of nodes)
    // +0x10: pFnTable (pointer to a function table used to call a method on each node)
    // The function table is an array of function pointers; the second entry (offset 0x04) is called with (node, 0).
};

struct ListNode {
    // +0x00: data / first field (unknown, maybe vtable pointer or value)
    // +0x04: next (pointer to next node)
};

void __fastcall ObjectList::releaseAll(int* this) {
    ListNode* node = (ListNode*)*this;  // head
    while (node) {
        // Store next node in the 'current' field
        *(int*)(this + 1) = *(int*)((int)node + 4);  // node->next
        // Call the virtual method at index 1 on the object referenced by pFnTable
        // param_1[4] is a pointer to a vtable-like array; offset 4 is the second function
        (**(code**)(*(int*)(this + 4) + 4))(node, 0);
        // Advance
        node = (ListNode*)*(this + 1);
        *(int*)this = (int)node;  // update head
    }
    // Clear the list state
    *(int*)(this + 1) = 0;  // current = null
    *(int*)this = 0;        // head = null
    *(int*)(this + 2) = 0;  // count = 0
}