// FUNC_NAME: GFObject::GFObject
GFObject* __thiscall GFObject::GFObject(unsigned char flags)
{
    // Call base initialization routine (likely base class constructor or initializer)
    initBase();

    // If the flag indicates a cleanup is required (e.g., placement new failure),
    // call the destructor via the vtable with the object size.
    if (flags & 1)
    {
        // Retrieve the class vtable pointer (static or singleton)
        int* vtable = (int*)getClassVTable();
        // vtable[1] (offset 4) is the destructor that takes an object size parameter
        // (typical EA EARS engine pattern for custom allocation/deallocation)
        typedef void (__thiscall* DestructorFunc)(GFObject*, unsigned int);
        ((DestructorFunc)vtable[1])(this, 0xA0);
    }

    return this;
}