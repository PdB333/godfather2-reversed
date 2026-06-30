// FUNC_NAME: SomeEARSObject::Constructor
// Address: 0x006bc380
// Role: Constructor with optional heap deallocation flag.
// The flag byte param_2 bit 0 indicates whether the object was allocated on heap.
// If set, the constructor calls operator delete(this, 0x190) after initialization.
// This is a common pattern in EA EARS engine for objects that can be both stack and heap allocated.
// Note: FUN_006bc180 is a separate constructor init function.
// Note: FUN_0043b960 is likely operator delete with size parameter.

undefined4 __thiscall SomeEARSObject::Constructor(byte allocFlag)
{
    this->init(); // Call base/initialization function (FUN_006bc180)
    if ((allocFlag & 1) != 0) {
        // Object was heap-allocated; free memory after construction.
        // 400 = 0x190 is the size of the object.
        ::operator delete(this, 0x190); // FUN_0043b960
    }
    return this; // Return the 'this' pointer as required by constructors.
}