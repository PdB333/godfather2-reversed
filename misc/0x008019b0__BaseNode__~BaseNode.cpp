// FUNC_NAME: BaseNode::~BaseNode
// Function address: 0x008019b0
// Destructor for a doubly-linked list node. Removes this node from the list and optionally deallocates memory.
// Offsets:
// +0x00: vtable pointer
// +0x18: previous node pointer
// +0x1c: next node pointer
// +0x20: data pointer (or replacement node)
// +0x28: vtable pointer (set to base vtable during destruction)

int __thiscall BaseNode::~BaseNode(BaseNode* this, byte deleteFlag)
{
    // Set vtable to base class vtable to avoid calling derived destructors again
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Remove this node from the doubly linked list
    if (*(BaseNode**)(this + 0x18) != nullptr) {
        BaseNode* prev = *(BaseNode**)(this + 0x18);
        BaseNode* next = *(BaseNode**)(this + 0x1c);
        BaseNode* data = *(BaseNode**)(this + 0x20);

        if (next == nullptr) {
            // No next node: set prev's +4 to data
            *(BaseNode**)(prev + 4) = data;
        } else {
            // Next exists: set next's +8 to data
            *(BaseNode**)(next + 8) = data;
        }

        if (data != nullptr) {
            // Update data's +4 to point to next
            *(BaseNode**)(data + 4) = next;
        }
    }

    // Call memory deallocation function (likely operator delete or custom allocator)
    FUN_0064d150();

    // If deleteFlag has bit 0 set, call additional cleanup/destruction
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return (int)this;
}