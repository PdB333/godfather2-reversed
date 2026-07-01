// FUNC_NAME: BaseObject::~BaseObject
int __thiscall BaseObject::~BaseObject(BaseObject* this, byte flags)
{
    // Set vtable to base class destructor vtable (0x00e317cc)
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // Unlink from linked list structure
    if (*(int*)(this + 0x18) != 0) // previous node or container
    {
        if (*(int*)(this + 0x1c) == 0) // next node is null
        {
            // Update previous node's next pointer to our data (offset +4 in previous)
            *(int*)(*(int*)(this + 0x18) + 4) = *(int*)(this + 0x20);
        }
        else
        {
            // Update next node's prev pointer to our data (offset +8 in next)
            *(int*)(*(int*)(this + 0x1c) + 8) = *(int*)(this + 0x20);
        }

        if (*(int*)(this + 0x20) != 0) // data pointer
        {
            // Update data's prev pointer (offset +4) to our next node
            *(int*)(*(int*)(this + 0x20) + 4) = *(int*)(this + 0x1c);
        }
    }

    // Call operator delete
    FUN_0064d150(this);

    // Scalar deleting destructor if flag bit 0 is set
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return this;
}