// FUNC_NAME: SomeListedNode::~SomeListedNode

int __thiscall SomeListedNode::~SomeListedNode(int this, byte deletingFlag)
{
    // +0x28: vtable pointer
    // +0x18: pointer to previous node in a linked list
    // +0x1c: pointer to next node in the same list
    // +0x20: pointer to an associated object (also linked with its own list at +0x4 and +0x8)
    // Set vtable to class-specific table (presumably to avoid virtual calls during destruction)
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Unlink the associated object from its own list.
    // The associated object (at +0x20) has forward pointer at +0x4 and backward pointer at +0x8.
    int* prevNode = *(int**)(this + 0x18);
    int* nextNode = *(int**)(this + 0x1c);
    int* associatedObj = *(int**)(this + 0x20);

    if (prevNode != 0) {
        if (nextNode == 0) {
            // No next node: set prevNode's forward pointer to the associated object
            *(int*)(prevNode + 1) = (int)associatedObj; // prevNode+4 = associatedObj
        } else {
            // Set nextNode's backward pointer to the associated object
            *(int*)(nextNode + 2) = (int)associatedObj; // nextNode+8 = associatedObj
        }
    }
    if (associatedObj != 0) {
        // Set the associated object's forward pointer to the next node
        *(int*)(associatedObj + 1) = (int)nextNode; // associatedObj+4 = nextNode
    }

    // Call base class destructor (likely handles own list unlink and cleanup)
    FUN_0064d150();

    // If the deleting flag's bit 0 is set, call operator delete
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete
    }

    return this;
}