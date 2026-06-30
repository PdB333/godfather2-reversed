// FUNC_NAME: Queue::pushBack
void __thiscall Queue::pushBack(Queue* this, QueueNode* source) // source in ESI
{
    // Structure of Queue:
    // +0x00: QueueNode* head
    // +0x04: QueueNode* tail
    // +0x08: int count
    // +0x0C: void* allocatorContext (can be nullptr, uses global default)
    // +0x10: IAllocator* allocator (has virtual allocate method)

    // Allocate new node (16 bytes)
    void* allocContext = (void*)this[0xC]; // param_1[3]
    if (allocContext == nullptr) {
        allocContext = &gDefaultAllocatorContext; // DAT_01218a14
    }
    // Call allocator's virtual allocate function (first vtable slot)
    QueueNode* newNode = (QueueNode*)this[0x10]->allocate(0x10, allocContext);
    // Copy source data (two dwords)
    newNode->data0 = source->data0;
    newNode->data1 = source->data1;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (this->tail != nullptr) {
        // Append after tail
        this->tail->next = newNode;
        newNode->prev = this->tail;
        QueueNode* newTail = this->tail->next; // could be simplified
        this->count++;
        this->tail = newTail; // update tail
    } else {
        // Empty list
        this->count++;
        this->head = newNode;
        this->tail = newNode;
    }
}