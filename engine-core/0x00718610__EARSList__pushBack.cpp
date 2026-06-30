// FUNC_NAME: EARSList::pushBack
void __fastcall EARSList::pushBack(EARSList* this, int value) {
    // Structure: this[0] = head, this[4] = tail, this[8] = count, this[12] = allocatorContext, this[16] = allocatorVTable*
    // Node layout: [0] data, [4] next, [8] prev
    ListNode* node;
    void* allocContext;

    // Determine allocator context (use global if none set)
    allocContext = this->allocatorContext;
    if (allocContext == nullptr) {
        allocContext = &g_defaultAllocContext; // DAT_01218a14
    }

    // Allocate node (size 0xc) via allocator virtual function
    void* allocatorVTable = *(void**)this->allocatorVTable;
    typedef void* (__thiscall *AllocateFunc)(void*, int, void*);
    AllocateFunc allocate = (AllocateFunc)allocatorVTable;
    node = (ListNode*)allocate(this->allocatorVTable, 0xc, allocContext);

    // Initialize node
    node->data = (void*)value; // from unaff_ESI
    node->next = nullptr;
    node->prev = nullptr;

    // Insert at tail
    if (this->tail != nullptr) {
        this->tail->next = node;
        node->prev = this->tail;
        ListNode* newTail = this->tail->next;
        this->count++;
        this->tail = newTail;
    } else {
        this->count++;
        this->head = node;
        this->tail = node;
    }
}