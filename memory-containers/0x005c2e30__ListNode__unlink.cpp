// FUNC_NAME: ListNode::unlink
// Function at 0x005c2e30: Removes this node from a doubly linked list by updating adjacent nodes' pointers.
// +0x0C: prev node pointer
// +0x10: next node pointer
void ListNode::unlink()
{
    // Update the previous node's next pointer if it exists
    if (this->prev != nullptr) {
        this->prev->next = this->next;
    }
    // Update the next node's prev pointer if it exists
    if (this->next != nullptr) {
        this->next->prev = this->prev;
    }
    // Check node validity (likely returns false if node is already in an invalid state)
    if (!this->checkValidity()) {
        // Call error handler from global manager table (DAT_012234ec + 4 -> object with vtable)
        (**(void (__thiscall **)(void))(**(int **)(DAT_012234ec + 4) + 4))();
    }
}