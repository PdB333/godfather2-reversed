// FUNC_NAME: ListNode::destroy
// Address: 0x0089c330 - Destructor with optional deallocation. Removes this node from a linked list and optionally frees memory.

class ListNode {
public:
    ListNode* prev;  // +0x18
    ListNode* next;  // +0x1c
    void* data;      // +0x20
    // vtable at +0x28

    void destroy(byte freeMemory);
};

void ListNode::destroy(byte freeMemory) {
    // Set vtable pointer
    *reinterpret_cast<int*>(this + 0x28) = reinterpret_cast<int>(&VTable_ListNode); // PTR_LAB_00e317cc

    if (this->prev != nullptr) {
        if (this->next == nullptr) {
            // Update data pointer in previous node's field at +4
            *reinterpret_cast<void**>(reinterpret_cast<int*>(this->prev) + 4) = this->data;
        } else {
            // Update data pointer in next node's field at +8
            *reinterpret_cast<void**>(reinterpret_cast<int*>(this->next) + 8) = this->data;
        }
        if (this->data != nullptr) {
            // Update the data object's field at +4 (e.g., next pointer)
            *reinterpret_cast<void**>(reinterpret_cast<int*>(this->data) + 4) = this->next;
        }
    }

    // Global cleanup routine (likely linked-list manager)
    someGlobalCleanup();

    // If requested, release memory using operator delete
    if (freeMemory & 1) {
        operator delete(this);
    }
}