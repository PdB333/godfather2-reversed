// FUNC_NAME: LinkedList::pushBack

void __fastcall LinkedList::pushBack(int* value)
{
    // List structure offsets (param_1 = this):
    // +0x00: head (ListNode*)
    // +0x04: tail (ListNode*)
    // +0x08: count (int)
    // +0x0C: allocator (void* or NULL -> use global DAT_01218a14)
    // +0x10: allocatorVtable (void*) - points to a vtable with allocation function at offset 0

    ListNode* newNode;
    ListNode* allocator;

    // Determine allocator (either from member or global)
    allocator = (ListNode*)this->allocator;
    if (allocator == nullptr) {
        allocator = (ListNode*)&DAT_01218a14; // global allocator
    }

    // Allocate a new node (size 0xC = 12 bytes)
    // The allocator's vtable first function is called with (size, allocator)
    newNode = (ListNode*)(*(void* (__fastcall**)(int, void*))(*((void**)this->allocatorVtable)))(0xC, allocator);
    if (newNode != nullptr) {
        newNode->data = *value;               // copy the first 4 bytes of value into the node
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }

    // Insert at tail
    if (this->tail != nullptr) {
        // List not empty: link after current tail
        this->tail->next = newNode;           // old tail's next -> newNode
        newNode->prev = this->tail;           // newNode's prev -> old tail
        this->count++;
        this->tail = newNode;                 // update tail
    } else {
        // List empty: head and tail point to newNode
        this->count++;
        this->head = newNode;
        this->tail = newNode;
    }
}