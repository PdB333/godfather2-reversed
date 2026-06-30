// FUNC_NAME: EARSObject::release
// Address: 0x005343f0
// Called to decrement reference count. Handles lifecycle (immediate deletion or deferred free list insertion).

void EARSObject::release()
{
    if (this == nullptr) return;

    // Get the reference count manager from vtable+8
    RefCountManager* mgr = (RefCountManager*)(*(int (__thiscall**)(EARSObject*))(*(uint*)this + 8))(this);

    // Access thread-local reference count table (FS:0x2C)
    int* threadData = (int*)__readfsdword(0x2C);
    int tableOffset = *(int*)(threadData + 2); // +0x08 in bytes

    // Check flags at this->field_0x10 + tableOffset
    uint flags = *(uint*)(this->field_0x10 + tableOffset);

    if ((flags & 0x10000000) != 0)
    {
        // Decrement a reference count in a table
        // this->field_0x04 + 0x10 points to an array of 0x24-byte entries
        int arrayBase = *(int*)(this->field_0x04 + 0x10);
        short index = this->field_0x0E; // offset 0x0E from this
        short* refCount = (short*)(arrayBase + 0x3E + index * 0x24);
        *refCount = *refCount - 1;
    }

    // Decrement the manager's reference count (offset 0x14)
    *(int*)(mgr + 0x14) = *(int*)(mgr + 0x14) - 1;

    if ((flags & 0x80000000) == 0)
    {
        // No deferred deletion flag -> call destructor (vtable+4)
        (*(void (__thiscall**)(EARSObject*))(*(uint*)this + 4))(this);
        return;
    }

    // Deferred deletion: insert this into the free list at mgr+0x1C
    this->field_0x08 = *(int*)(mgr + 0x1C);
    *(int**)(mgr + 0x1C) = this;
}