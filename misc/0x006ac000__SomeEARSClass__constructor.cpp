// FUNC_NAME: SomeEARSClass::constructor
// Address: 0x006ac000
// Role: Constructor for a class of size 0x5c (92 bytes).
// Sets vtable, initializes two interface pointers, constructs a subobject at offset 0x14,
// then calls global initialization routines. If allocFlags bit 0 is set, frees memory.

undefined4 * __thiscall SomeEARSClass::constructor(undefined4 *this_, byte allocFlags)
{
    // Set primary vtable pointer
    *this_ = &PTR_FUN_00d5da8c;

    // Set secondary function table pointers (offsets 0x3C and 0x48)
    this_[0xf] = &PTR_LAB_00d5da7c;   // +0x3C: vtable2
    this_[0x12] = &PTR_LAB_00d5da78;  // +0x48: vtable3

    // Initialize subobject at offset 0x50 (this_+0x14)
    // First constructor call
    FUN_004086d0(this_ + 0x14);       // subObjectConstructor(this_ + 0x50)
    // Additional initialization
    FUN_00408310(this_ + 0x14);       // subObjectInitialize(this_ + 0x50)

    // Initialize global static instance (likely same type as subobject)
    FUN_004086d0(&DAT_0120e93c);      // subObjectConstructor(&globalStaticSubobject)

    // Perform global one-off initialization
    FUN_0046c640();                   // globalInit()

    // If allocFlags indicates this was allocated via operator new, free memory
    if ((allocFlags & 1) != 0) {
        FUN_0043b960(this_, 0x5c);    // operator delete(this_, 92)
    }

    return this_;
}