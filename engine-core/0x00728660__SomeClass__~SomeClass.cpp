// FUNC_NAME: SomeClass::~SomeClass
// ADDRESS: 0x00728660
// ROLE: Destructor (or cleanup function) for a class with vtable at offset 0, 
//       function pointers at offsets 0x3C and 0x48, a flag at offset 0x5E, 
//       and a pointer at offset 0x9C. Sets vtable to a zombie table and releases members.

void __thiscall SomeClass::~SomeClass()
{
    // Set vtable to zombie/destructor table to prevent virtual calls during destruction
    *(void**)this = &PTR_FUN_00d62498;
    // Set function pointers at offsets 0x3C and 0x48 to null tables? (likely null functions)
    *(void**)((int)this + 0x3C) = &PTR_LAB_00d62488;
    *(void**)((int)this + 0x48) = &PTR_LAB_00d62484;

    // If flag at offset 0x5E has bit 0 set, release some pointer at offset 0x50
    if ((*(byte*)((int)this + 0x5E) & 1) != 0) {
        FUN_00729980(*(void**)((int)this + 0x50));  // Release member resource
    }

    // If pointer at offset 0x9C is not null, call its destructor/free
    if (*(void**)((int)this + 0x9C) != 0) {
        FUN_004daf90((void**)((int)this + 0x9C));  // Likely operator delete on a subobject
    }

    // Global cleanup or debug hook
    FUN_0046c640();
}