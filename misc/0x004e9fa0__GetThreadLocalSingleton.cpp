// FUNC_NAME: GetThreadLocalSingleton
struct PerThreadContext {
    /* +0x00 */ int field_0; // set to 0
    /* +0x04 */ int field_4; // set to 0
    /* +0x08 */ int field_8; // set to -1
    // ... other fields up to offset 0x9C (0x27*4) and 0xA0 (0x28*4)
    /* +0x9C */ int field_9C; // set to 0
    /* +0xA0 */ int field_A0; // set to -1
    // size 0x134
};

// __cdecl (no this)
PerThreadContext* GetThreadLocalSingleton(void)
{
    // Access the first thread-local storage slot (slot 0), which holds a pointer to a PerThreadContext.
    // FS:[0x2c] -> pointer to TLS array; [TLS array] -> first slot value
    int* tlsSlot = *(int**)(__readfsdword(0x2c)); // read pointer to TLS array
    PerThreadContext* context = (PerThreadContext*)*tlsSlot; // first TLS slot value

    // Check if the per-thread context has already been initialized (field at +0x2c is non-zero?)
    if (context->field_2c == 0) // but field_2c not in struct? Actually check condition: *(int*)(context + 0x2c) == 0
    {
        // Allocate a new PerThreadContext with custom allocator
        // Allocator parameters: size=0x134, flags=2, alignment=0x10, unknown=0
        AllocationParams params;
        params.flags = 2;
        params.alignment = 0x10;
        params.unknown = 0;

        PerThreadContext* newContext = (PerThreadContext*)FUN_009c8ed0(0x134, &params);

        if (newContext != nullptr)
        {
            // Initialize fields
            newContext->field_4 = 0;
            newContext->field_8 = -1;
            newContext->field_9C = 0;
            newContext->field_A0 = -1;
            // Store the newly allocated context into the first TLS slot
            *tlsSlot = (int)newContext;
            newContext->field_0 = 0;
            return newContext;
        }
        // Allocation failed; clear the TLS slot
        *tlsSlot = 0;
    }
    // Return existing context from TLS slot
    return (PerThreadContext*)*tlsSlot;
}