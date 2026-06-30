// FUNC_NAME: SomeClass::~SomeClass
void * __thiscall SomeClass::~SomeClass(bool deleteFlag)
{
    // Call base destructor or actual destructor body (takes first member, likely vtable or base pointer)
    FUN_009c8f10(*this);
    // If deleteFlag is set (bit 0), deallocate memory via operator delete
    if (deleteFlag)
    {
        FUN_009c8eb0(this);
    }
    return this;
}