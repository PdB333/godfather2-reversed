// FUNC_NAME: LinkedList::clear
void LinkedList::clear(void)
{
    int* currentHead; // eax
    int* nodeToRemove; // unaff_EDI[1] used as temporary

    currentHead = this->head; // +0x00: head pointer
    while (currentHead != nullptr) {
        nodeToRemove = this->tail; // +0x04: tail pointer
        if (nodeToRemove != nullptr) {
            // Unlink nodeToRemove from the list
            this->tail = nodeToRemove->next; // node offset +0x10: next
            if (this->head == nodeToRemove) {
                this->head = nodeToRemove->next; // +0x10: next
            }
            if (nodeToRemove->prev != nullptr) { // offset +0x0C: prev
                nodeToRemove->prev->next = nodeToRemove->next; // +0x10: next
            }
            if (nodeToRemove->next != nullptr) { // +0x10: next
                nodeToRemove->next->prev = nodeToRemove->prev; // +0x0C: prev
            }
            bool shouldFree = FUN_005c43d0(nodeToRemove); // called on the node
            if (!shouldFree) {
                // Call memory manager deallocation (likely operator delete)
                // DAT_012234ec points to a memory manager singleton
                (**(code**)(*(int**)(DAT_012234ec + 4) + 4))(nodeToRemove, 0);
            }
        }
        if (this->tail == nullptr) {
            this->tail = this->head; // reset tail to head if list became empty? Actually this sets tail to head for next iteration
        }
        currentHead = this->head; // update loop condition
    }
}