// FUNC_NAME: Container::initList
void Container::initList(void)
{
    // this: pointer passed in EAX, structure with vtable at offset 0 and field at +4
    void* vtable = *(void**)this;                  // +0x00 vtable pointer
    int someField = *(int*)((char*)this + 4);       // +0x04 some integer field

    // Call virtual function at vtable offset 8 (likely release/clear)
    (*(void (__thiscall**)(void*))((char*)vtable + 8))(this);

    // If the field is nonzero, convert it via FUN_004265d0 (possibly a handle or ID)
    undefined4 converted = 0;
    if (someField != 0) {
        converted = FUN_004265d0(someField, this);
    }

    // Call another initialization function
    FUN_00622f60(this, this, converted);

    // Allocate a new node (size >= 0x26 bytes)
    ListNode* node = (ListNode*)FUN_00623880();

    // Store node pointer at offset 0x1c of this object
    *(ListNode**)((char*)this + 0x1c) = node;

    // Initialize node as a circular sentinel (doubly linked list with extra pointer)
    node->flag25 = 1;                              // +0x25 byte flag
    node->prev = node;                             // +0x00 self-loop
    node->next = node;                             // +0x04 self-loop
    node->extra = node;                            // +0x08 self-loop (maybe list head or data)

    // Zero field at offset 0x20
    *(int*)((char*)this + 0x20) = 0;
}