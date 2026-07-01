// FUNC_NAME: LinkedListContainer::~LinkedListContainer
// Function address: 0x008e6fe0
// Destructor for a class containing a singly-linked list.
// Clears the list by setting each node's data and next pointer to 0,
// but does not free the nodes themselves. If param_2 & 1, deallocates this instance.

class LinkedListContainer {
public:
    // VTable pointer (set to 0x00e32808)
    void *vtable;                         // +0x00
    ListNode *head;                       // +0x04 (param_1[1])

    __thiscall ~LinkedListContainer() {
        // Destructor
        vtable = &PTR_FUN_00e32808;       // vtable assignment

        // Clear the linked list: reset each node to zero
        ListNode *current = head;
        while (current != nullptr) {
            ListNode *next = current->next;   // +0x04 (offset 1)
            current->next = nullptr;
            current->data = 0;               // +0x00
            current = next;
        }

        // The list is cleared but nodes are not freed (they may be owned elsewhere)
    }

    // Note: Actual destructor called with a byte param (0 or 1) indicating whether to call operator delete.
    // In this reconstruction, we assume the caller handles deallocation if needed.
};

// Node structure for the linked list
struct ListNode {
    int data;         // +0x00
    ListNode *next;   // +0x04
};
```