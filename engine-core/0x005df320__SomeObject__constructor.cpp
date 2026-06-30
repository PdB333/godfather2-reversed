// FUNC_NAME: SomeObject::constructor
SomeObject* __thiscall SomeObject::constructor(SomeObject* thisPtr, byte constructionFlags)
{
    // Set vtable pointer (class-specific vtable at 0x00e3f2d8)
    *thisPtr = &PTR_FUN_00e3f2d8;

    // Call base class constructor
    baseConstructor();

    // If construction flag bit 0 is set, perform post-construction initialization
    if (constructionFlags & 1)
    {
        postConstructionInit(thisPtr);
    }

    return thisPtr;
}