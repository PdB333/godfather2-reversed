// FUNC_NAME: FixedList::pushFront
uint __fastcall FixedList::pushFront(FixedList* this, void* node) {
    uint result = 1; // initializing to 1 in EAX? but decompiler shows in_EAX & 0xffffff00, so assume success
    // offset 10: count, offset 8: capacity
    if (this->count < this->capacity && node != nullptr) {
        if (this->count == 0) {
            // Empty list: set head to new node
            this->head = node; // offset 0
        } else {
            // Non-empty: attach new node before current head (stored at offset 4)
            void* oldHead = this->lastInserted; // offset 4
            if (oldHead == nullptr) return 0; // defensive
            ((Node*)oldHead)->prev = node; // set old head's prev to new node
        }
        // Common link
        ((Node*)node)->next = this->lastInserted; // set new node's next to previous head
        ((Node*)node)->prev = nullptr; // new node becomes head, prev is null
        this->count++;
        this->lastInserted = node; // update "last inserted" pointer (now the new head)
        result = 1; // success indicator (in EAX)
    }
    return result;
}