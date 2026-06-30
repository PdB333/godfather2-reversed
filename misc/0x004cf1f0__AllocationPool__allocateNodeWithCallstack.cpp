// FUNC_NAME: AllocationPool::allocateNodeWithCallstack
void __thiscall AllocationPool::allocateNodeWithCallstack(void *data) {
    // +0x4: pointer to a pre-allocated buffer or null
    char *buffer = *(char **)((char *)this + 4);
    char localBuffer[12]; // temporary stack buffer when no pre-allocated one

    if (buffer == nullptr) {
        // Initialize temporary buffer to zero
        localBuffer[0] = 0;
        localBuffer[4] = 0;
        localBuffer[8] = 0;
        buffer = localBuffer;
    }

    // Virtual function at vtable index 0: allocate(size, placementHint)
    // Typically a custom allocator from the EA EARS engine
    typedef void *(__thiscall *AllocFunc)(void *, int, void *);
    AllocFunc allocFn = (AllocFunc)(*(void ***)this)[0];
    Node *node = (Node *)allocFn(this, 12, buffer);

    if (node != nullptr) {
        // Initialize the 12-byte node
        node->field0 = localBuffer[8];           // first field (0 from temporary buffer, undefined otherwise)
        node->field1 = (void *)__builtin_return_address(0); // capture call site (return address)
        node->field2 = *(int *)data;             // first 4 bytes of input data
    }
}