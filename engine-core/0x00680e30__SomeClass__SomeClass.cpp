// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00680e30
// Role: Constructor for a class with vtable at offset 0x20; sets a global flag and performs sub-initialization.
// The allocFlag parameter's LSB indicates whether dynamic deallocation should be called (likely a placement new destructor trigger).

int __thiscall SomeClass::SomeClass(SomeClass *this, byte allocFlag)
{
    // Set vtable pointer at offset 0x20 from this
    if (this != nullptr) {
        *(void **)((char *)this + 0x20) = &PTR_LAB_00d580ec; // vtable reference
    }
    // Global initialization
    DAT_01129920 = 0; // likely a singleton or state flag
    // Sub-initialization call
    FUN_007edfb0();
    // If alloc flag LSB is set, perform cleanup/deallocation
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this); // possibly operator delete or destructor
    }
    return (int)this;
}