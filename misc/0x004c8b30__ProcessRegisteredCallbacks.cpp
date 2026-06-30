// FUNC_NAME: ProcessRegisteredCallbacks
// Address: 0x004c8b30
// Role: Iterates over a global linked list of registered callback objects and invokes their first virtual function with argument 1.
// Used for processing or ticking a set of registered listeners/updaters.

struct RegisteredCallbackNode {
    // +0x00: Pointer to virtual function table (or array of function pointers)
    void (**vtable)(); // treated as __cdecl, but first entry is called with (int)
    // +0x04: Unknown field (possibly data)
    // +0x08: Next node in the linked list
    RegisteredCallbackNode* next;
};

// Global head pointer at 0x012054a8
static RegisteredCallbackNode* gRegisteredCallbackHead = (RegisteredCallbackNode*)0x012054a8;

void ProcessRegisteredCallbacks(void)
{
    if (gRegisteredCallbackHead != nullptr) {
        do {
            RegisteredCallbackNode* current = gRegisteredCallbackHead;
            // Advance head to next node (offset +0x08)
            gRegisteredCallbackHead = current->next;
            // Call the first function pointer in the vtable with argument 1
            // The function signature is void (int)
            ((void (*)(int))(*(current->vtable)))(1);
        } while (gRegisteredCallbackHead != nullptr);
    }
}