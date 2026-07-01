// FUNC_NAME: SimObject::~SimObject
int __thiscall SimObject::~SimObject(void* this, unsigned char flags)
{
    // Set vtable to base class vtable (likely virtual destructor chain)
    *(void***)((int)this + 0x28) = &PTR_LAB_00e317cc;

    // Remove from intrusive linked list
    // Offsets: +0x18 = previous node, +0x1c = next node, +0x20 = self node (may be this itself)
    void* prevNode = *(void**)((int)this + 0x18);
    void* nextNode = *(void**)((int)this + 0x1c);
    void* selfNode = *(void**)((int)this + 0x20);

    if (prevNode != nullptr)
    {
        if (nextNode == nullptr)
        {
            // Only a previous node exists: update its forward link (offset +4) to selfNode
            *(void**)((int)prevNode + 4) = selfNode;
        }
        else
        {
            // Both previous and next nodes exist: update next node's backward link (offset +8) to selfNode
            *(void**)((int)nextNode + 8) = selfNode;
        }
    }

    if (selfNode != nullptr)
    {
        // Update selfNode's forward link (offset +4) to nextNode
        *(void**)((int)selfNode + 4) = nextNode;
    }

    // Call base class destructor (likely SimObject base or similar)
    FUN_0064d150();

    // If flags bit 0 is set, deallocate memory
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return (int)this;
}