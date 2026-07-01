// FUNC_NAME: GenericListNode::~GenericListNode
int __thiscall GenericListNode::~GenericListNode(GenericListNode* this, byte flags)
{
    // Set vtable pointer (likely for base class or debugging)
    *(void***)((int)this + 0x28) = &PTR_LAB_00e317cc;

    // Remove this node from an intrusive linked list.
    // List node pointers are at offsets +0x18, +0x1c, +0x20.
    // The structure appears to be:
    //   +0x18: pointer to next node
    //   +0x1c: pointer to previous node
    //   +0x20: pointer to self (maybe payload or dummy)
    GenericListNode* next = *(GenericListNode**)((int)this + 0x18);
    GenericListNode* prev = *(GenericListNode**)((int)this + 0x1c);
    GenericListNode* self = *(GenericListNode**)((int)this + 0x20);

    if (next != nullptr) {
        if (prev == nullptr) {
            // Update next node's back pointer (at +0x04) to point to self
            *(GenericListNode**)((int)next + 0x04) = self;
        } else {
            // Update previous node's forward pointer (at +0x08) to point to self
            *(GenericListNode**)((int)prev + 0x08) = self;
        }
    }
    if (self != nullptr) {
        // Update self's back pointer (at +0x04) to point to prev
        *(GenericListNode**)((int)self + 0x04) = prev;
    }

    // Call base class destructor (likely virtual dispatch)
    FUN_0064d150();

    // If flags bit 0 is set, deallocate memory
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return (int)this;
}