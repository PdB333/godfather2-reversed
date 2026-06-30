// FUNC_NAME: PoolAllocator::initialize
PoolAllocator* PoolAllocator::initialize()
{
    Allocator* allocator = this->allocator;          // +0x00: pointer to allocator with vtable
    int userData = this->userData;                   // +0x04: optional user context
    allocator->vtable->somePreprocess(allocator);    // vtable index 2 (offset 0x08)

    int param = (userData != 0) ? SomeConversionFunc(userData, allocator) : 0;
    ExternalFunction(this, allocator, param);        // likely registers this pool with allocator

    // If no user data, use stack dummy (zeroed)
    int dummy[3] = {0, 0, 0};
    void* client = (userData != 0) ? (void*)userData : dummy;

    // Allocate a node (32 bytes) from the allocator
    ListNode* node = (ListNode*)allocator->vtable->allocate(allocator, 0x20, client);
    if (node != nullptr)
    {
        node->prev = node;   // Initialize doubly linked list node (self-loop)
        node->next = node;
    }

    this->head = node;       // +0x18: list head
    this->count = 0;         // +0x1C: element count
    return this;
}