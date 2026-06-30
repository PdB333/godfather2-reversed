// FUNC_NAME: Object::decrementPendingOperations
int __fastcall Object::decrementPendingOperations(int this)
{
    int previousResult = *(int *)(this + 0x1c); // +0x1c: result/state variable
    // First call to process one item (possibly as a side effect)
    FUN_00635d00(0xffffffff); // process a pending operation

    // Check if the 'dirty' or 'lock' flag is clear in the pending operations structure
    // +0x14: pointer to a PendingOps structure
    // PendingOps+0x08: flags byte
    PendingOps* ops = *(PendingOps**)(this + 0x14);
    if ((ops->flags & 1) == 0)
    {
        int* countPtr = &ops->count; // PendingOps+0x14: counter of pending items
        // Process all pending operations by decrementing the count and calling the helper
        while (*countPtr != 0)
        {
            (*countPtr)--;
            FUN_00635d00(0xffffffff); // process one item
        }
        // Final decrement (possibly for the parent object itself)
        (*countPtr)--;
    }
    // The return value is the original EAX (preserved through all side effects)
    return *(int *)(this + 0x1c) + (in_EAX - previousResult);
}

// Helper structure assumed from offsets
struct PendingOps {
    byte unknown[8]; // +0x00..0x07
    byte flags;      // +0x08
    byte padding[11]; // +0x09..0x13
    int count;       // +0x14
};