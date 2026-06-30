// FUNC_NAME: ListContainer::removeAllMatchingKey(int key)
void __thiscall ListContainer::removeAllMatchingKey(int key) {
    ListNode* current = head;      // start from head
    ListNode* nextToProcess = head; // iterator used for safe removal

    while (current != nullptr) {
        if (nextToProcess == nullptr) {
            current = nullptr;
        } else {
            current = nextToProcess->next; // +0x10
        }

        ListNode* newNext = current;
        if (current == nullptr) {
            newNext = head; // restart from head if we ran out
        }
        nextToProcess = newNext;

        if (current != nullptr && current->key == key) { // +0x04
            // Update the safe iterator if we just removed the node it points to
            if (nextToProcess == current) {
                nextToProcess = current->next; // +0x10
            }

            // Remove current from doubly linked list
            if (head == current) {
                head = current->next; // +0x10
            }
            if (current->prev != nullptr) { // +0x0C
                current->prev->next = current->next; // +0x10
            }
            if (current->next != nullptr) { // +0x10
                current->next->prev = current->prev; // +0x0C
            }

            // Check if node can be freed
            bool canFree = FUN_005c43d0(current); // some condition
            if (!canFree) {
                // Call global deallocation function (vtable slot +4 of some manager)
                (**(code**)(**(int**)(DAT_012234ec + 4) + 4))(current, 0);
            }
        }
    }
}