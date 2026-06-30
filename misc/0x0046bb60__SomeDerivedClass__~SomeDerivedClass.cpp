// FUNC_NAME: SomeDerivedClass::~SomeDerivedClass
void * __thiscall SomeDerivedClass::~SomeDerivedClass(void *this, byte deletingFlag)
{
    // Switch vtable to base before calling base destructor
    ((SomeDerivedClass *)this)->vtable = (void *)&SomeBaseClass::vtable; // 0x00e32768
    // Call base destructor (FUN_0043e380)
    ((SomeBaseClass *)this)->~SomeBaseClass();
    // Restore vtable to derived (for consistency, though object is being destroyed)
    ((SomeDerivedClass *)this)->vtable = (void *)&SomeDerivedClass::vtable; // 0x00e30ea0
    // If the object was heap-allocated, free the memory
    if ((deletingFlag & 1) != 0) {
        operator delete(this); // FUN_009c8eb0
    }
    return this;
}