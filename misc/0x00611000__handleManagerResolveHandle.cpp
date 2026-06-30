// FUNC_NAME: handleManagerResolveHandle

// Function at 0x00611000: Looks up a handle value in a hash table and returns associated data.
// Used by multiple subsystems (entity manager, resource cache, etc.)
// The hash table uses the lower 12 bits of the handle as a bucket index,
// then traverses a singly linked list to find the node with matching handle.
// Returns 0 if handle is 0, data pointer if found, or -1 (0xFFFFFFFF) on failure.

// Handle node structure (based on decompiled offsets)
struct HandleNode {
    uint32_t unknown0;  // +0x00: not used in this function
    void*    data;      // +0x04: the returned value (pointer or ID)
    // ... potential other fields ...
    uint32_t handle;    // +0x34: the handle key
    HandleNode* next;   // +0x38: next node in collision chain
};

// Global hash table: array of 4096 bucket heads (indexed by (handle & 0xFFF))
// Points to first node in each bucket chain.
extern HandleNode** g_handleTable; // At DAT_012058e0

void* handleManagerResolveHandle(uint32_t handleID)
{
    // Handle 0 maps to null pointer
    if (handleID == 0) {
        return 0;
    }

    // Determine bucket index from lower 12 bits
    uint32_t bucketIndex = handleID & 0xFFF;
    HandleNode* node = g_handleTable[bucketIndex];

    // Search the linked list for the matching handle
    while (node != nullptr) {
        if (node->handle == handleID) {
            // Found: return the associated data (+0x04)
            return node->data;
        }
        node = node->next; // +0x38: next node in chain
    }

    // Not found: return error (-1 cast to pointer)
    return (void*)0xFFFFFFFF;
}