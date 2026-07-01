// FUNC_NAME: EARSObject::EARSObject (constructor taking an argument)
// Function at 0x00824f20: initializes a derived EARS object, sets vtable, and handles base construction cleanup

void EARSObject::EARSObject(uint arg)
{
    // On-stack temporary arrays – likely representing the base class portion of the object
    // The first 23 pointers store vtable pointers (for multiple inheritance or interface table)
    void* baseVtableArray[23];
    // Flags / reference count – size 8 ints (32 bytes)
    int constructionFlags[8];

    // Call base class constructor.
    // It initializes the base part using this (param_1) and arg (param_2)
    BaseEARSObject::construct(baseVtableArray, this, arg);

    // Override the first vtable pointer with the derived class vtable
    baseVtableArray[0] = &PTR_FUN_00d7343c; // derived vtable

    // If the base constructor encountered an error or needs special cleanup,
    // release resources via the base destructor
    if (constructionFlags[0] != 0) {
        BaseEARSObject::destroy(constructionFlags);
    }
}