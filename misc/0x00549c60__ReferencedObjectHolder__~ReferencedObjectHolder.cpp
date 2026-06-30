// FUNC_NAME: ReferencedObjectHolder::~ReferencedObjectHolder

void __thiscall ReferencedObjectHolder::~ReferencedObjectHolder(byte destroyObject)
{
    // Set vtable to base class (vtable for this destructor chain)
    *(void**)this = &PTR_FUN_00e39bc8;

    // Reference to a ref-counted object stored at +0xC0 (param_1[0x30])
    RefCountedObject* refObj = *(RefCountedObject**)((int)this + 0xC0);
    if (refObj != nullptr)
    {
        // Check if strong reference count (short at +4) is non-zero
        if (*(short*)((int)refObj + 4) != 0)
        {
            // Decrement weak reference count? (short at +6)
            short newWeakCount = *(short*)((int)refObj + 6) - 1;
            *(short*)((int)refObj + 6) = newWeakCount;
            if (newWeakCount == 0)
            {
                // Call vtable[0] with argument 1 (likely release/deleting shared object)
                (*(void(__thiscall**)(RefCountedObject*, int))refObj)(refObj, 1);
            }
        }
        // Clear pointer
        *(RefCountedObject**)((int)this + 0xC0) = nullptr;
    }

    // If requested, destroy the holder itself (bit 0 of destroyObject)
    if (destroyObject & 1)
    {
        // Custom deallocator for this class (FUN_009c8eb0)
        FUN_009c8eb0(this);
    }
}