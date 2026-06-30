// FUNC_NAME: LinkedListNode::unlink
// Function at 0x004b1500: Removes this node from its singly linked list with sentinel head.
// Each node contains a pointer to the list head at +0x00 and a next pointer at +0x04.
// The sentinel head's next pointer at +0x04 points to the first real element.
// If freeMemory (param_2 & 1) is nonzero, the node's memory is freed via FUN_009c8eb0.

class LinkedListNode {
public:
    LinkedListNode* listHead; // +0x00: pointer to list sentinel head
    LinkedListNode* next;     // +0x04: next node in list

    // Removes this node from the list. Returns this (after possible deallocation).
    LinkedListNode* __thiscall unlink(byte freeMemory) {
        LinkedListNode* head = this->listHead;
        if (head != nullptr) {
            LinkedListNode* first = head->next; // first real node
            if (first == this) {
                // This node is the first element; bypass it from head
                head->next = this->next;
            } else {
                // Traverse to find the node whose next is this
                LinkedListNode* prev = first;
                LinkedListNode* curr = prev->next;
                while (curr != this) {
                    prev = curr;
                    curr = prev->next;
                }
                prev->next = this->next;
            }
        }
        if ((freeMemory & 1) != 0) {
            // Custom deallocator (likely operator delete or pool free)
            FUN_009c8eb0(this);
        }
        return this;
    }
};