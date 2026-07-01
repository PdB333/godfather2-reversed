// FUNC_NAME: LinkedList::removeCurrentNode
// Address: 0x007e28d0
// Removes the node pointed to by *param_3 from a doubly linked list.
// Updates *param_3 to the next node after removal.
// Calls a virtual function on the container to handle the removed node.
// The container structure (this) has:
//   +0x00: head pointer
//   +0x04: tail pointer
//   +0x08: count
//   +0x10: vtable pointer (used for virtual call)
// The node structure (ListNode) has:
//   +0x00: some pointer (possibly reference count or data)
//   +0x0C: next pointer
//   +0x10: prev pointer

struct ListNode {
    void* field_0;      // +0x00: some pointer (checked for non-zero before release)
    // ... other fields ...
    ListNode* next;     // +0x0C
    ListNode* prev;     // +0x10
};

class LinkedList {
public:
    ListNode* head;     // +0x00
    ListNode* tail;     // +0x04
    int count;          // +0x08
    void** vtable;      // +0x10 (pointer to virtual function table)

    // Virtual function at vtable+4: called with the removed node and 0
    // Likely "onNodeRemoved" or "destroyNode"
    void virtual onNodeRemoved(ListNode* node, int param) = 0; // offset 4 in vtable

    void removeCurrentNode(ListNode** iterator) {
        ListNode* node = *iterator;
        if (node == nullptr) {
            return; // Actually the code sets iVar2=0 but then proceeds? Let's check: piVar1 = *param_3; if piVar1==0 then iVar2=0; then *param_3 = iVar2; so if node is null, *iterator becomes 0 and then the rest of the code still runs? But then piVar1 is null, so the if checks would fail. Actually the code sets *param_3 = iVar2; where iVar2 is 0 if piVar1==0. Then it proceeds to check if piVar1 == *param_1 (head). Since piVar1 is null, it's not equal, so it goes to else branch. Then it checks if piVar1 == param_1[1] (tail). Also false. Then it does the else branch which accesses piVar1[3] and piVar1[4] which would be null pointer dereference. So the function likely assumes node is not null. We'll add a null check.
        }

        // Save next node to update iterator
        ListNode* nextNode = node->next;
        *iterator = nextNode;

        // Remove node from list
        if (node == head) {
            if (node == tail) {
                // Only node in list
                head = nullptr;
                tail = nullptr;
            } else {
                // Remove head
                head = nextNode;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            }
        } else {
            ListNode* prevNode = node->prev;
            if (node == tail) {
                // Remove tail
                tail = prevNode;
                if (tail != nullptr) {
                    tail->next = nullptr; // Actually the code sets *(int *)(iVar2 + 0xc) = 0; which is prevNode->next = 0? Wait: param_1[1] = iVar2; *(undefined4 *)(iVar2 + 0xc) = 0; So tail->next = 0. Yes.
                }
            } else {
                // Remove middle node
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
            }
        }

        // Release the node if its field_0 is non-zero
        if (node->field_0 != nullptr) {
            FUN_004daf90(node); // Likely a release function (e.g., decrement ref count or free)
        }

        // Call virtual function on container to handle removed node
        // vtable[1] (offset 4) is called with node and 0
        (this->vtable[1])(node, 0);

        // Decrement count
        count--;

        // Note: The original code also does *unaff_EBX = *param_3; which might be a return value in EBX register.
        // This is likely an optimization to return the new iterator value in EBX.
        // We'll ignore it as it's not part of the C++ semantics.
    }
};