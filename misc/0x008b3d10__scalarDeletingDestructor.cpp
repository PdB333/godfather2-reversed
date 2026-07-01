// FUNC_NAME: scalarDeletingDestructor
// Address: 0x008b3d10
// Role: Scalar deleting destructor for an unknown class (EA EARS engine)
// Pattern: calls destructor on member at +0x14, then optionally deletes this

int __thiscall scalarDeletingDestructor(void* this, unsigned char flags)
{
    // Call destructor on the object stored at this+0x14 (likely a pointer to a sub-object or resource)
    // Assuming FUN_009c8f10 is the actual destructor for that object
    FUN_009c8f10(*(void**)((char*)this + 0x14)); // +0x14: member pointer (e.g., m_pResource)

    // If the flag (bit 0) is set, free the memory of this object
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // operator delete or free
    }

    return (int)this; // return this pointer (standard for scalar deleting destructor)
}