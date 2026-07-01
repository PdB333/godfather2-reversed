// FUNC_NAME: UnknownClass::~UnknownClass
void * __thiscall UnknownClass::~UnknownClass(void *this, byte flags)
{
    // Set vtable to base class vtable for proper virtual dispatch during destruction
    // Base class vtable at 0x00d6b95c
    *(void **)this = &PTR_LAB_00d6b95c;

    // Call base class destructor
    BaseClassDestructor(this);

    // If object was heap-allocated (flags & 1), deallocate memory
    if (flags & 1)
    {
        operator delete(this);
    }

    return this;
}