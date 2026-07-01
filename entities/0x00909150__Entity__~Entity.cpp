// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(int this) {
    // Stack cookie sentinel (common in debug builds for list iteration)
    int* sentinel = (int*)&local_18;
    int* sentinelPtr = &PTR_FUN_00e31e2c;  // global list head or vtable

    // Get pointer to node at offset 0x48 (likely a linked list of components or children)
    int* node;
    if (this == 0) {
        node = 0;
    } else {
        node = (int*)(this + 0x48);
    }

    int* nextPtr = 0;
    if (node != 0) {
        // Read next pointer (offset +4) and then set node->next to &node (mark as detached)
        nextPtr = *(int**)(node + 4);
        *(int***)(node + 4) = &node;  // node->next = address of local variable (stack) – actually sets to self for list removal
    }

    // Release reference at offset 0xC4 (e.g., smart pointer to another object)
    void* ref = *(void**)(this + 0xC4);
    int flag = 0;
    FUN_00408a00(&ref, flag);  // release/decrement refcount

    // If node existed, call a function that finalizes removal (likely adds node to free list)
    if (node != 0) {
        FUN_004daf90(&node);
    }
}