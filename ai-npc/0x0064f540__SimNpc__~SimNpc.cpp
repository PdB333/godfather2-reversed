// FUNC_NAME: SimNpc::~SimNpc
void __thiscall SimNpc::~SimNpc()
{
    // Set vtable to base class vtable (prevent virtual calls during destruction)
    *(void**)this = &PTR_LAB_00e42f48; // +0x00

    // Generic destructor preamble (component cleanup, etc.)
    FUN_00652df0(); // likely some pre-cleanup

    // Conditional cleanup of a resource pointed to at +0x1FC
    if (*(void**)((char*)this + 0x1FC) != 0) {
        FUN_00650de0(*(void**)((char*)this + 0x1FC)); // release component at +0x1FC
    }

    // Another cleanup function
    FUN_00650d80(); // likely releases some other components

    // Free memory of resources at offsets +0x210, +0x218, +0x214, +0x1FC
    operatorDelete(*(void**)((char*)this + 0x210)); // +0x210
    operatorDelete(*(void**)((char*)this + 0x218)); // +0x218
    operatorDelete(*(void**)((char*)this + 0x214)); // +0x214
    operatorDelete(*(void**)((char*)this + 0x1FC)); // +0x1FC

    // Remove node from a doubly linked list (pointers at +0x21C, +0x220, +0x224)
    void* node = *(void**)((char*)this + 0x21C); // +0x21C: pointer to list node
    if (node != 0) {
        void* prev = *(void**)((char*)this + 0x220); // +0x220: previous node pointer
        void* next = *(void**)((char*)this + 0x224); // +0x224: next node pointer

        // Standard removal from doubly linked list
        if (prev == 0) {
            // node is the head: update its next pointer
            *(void**)((char*)node + 4) = next; // node->next = next
        } else {
            // node is not head: update prev's next pointer
            *(void**)((char*)prev + 8) = next; // prev->next = next
        }
        if (next != 0) {
            // Update next's prev pointer
            *(void**)((char*)next + 4) = prev; // next->prev = prev
        }
    }

    // Call base class destructor
    FUN_0064e060(); // ~Entity or similar
}