// FUNC_NAME: ObjectBase::constructor
// Address: 0x0090fc60
// Role: Constructor with allocation flag - calls base constructor then optionally performs cleanup/deallocation.
// param_2: byte flag; if bit 0 set, calls internal deallocation function (possibly operator delete or destructor).

undefined4 __thiscall ObjectBase::constructor(byte param_2)
{
    // Call base constructor (likely initializes vtable and core fields)
    baseConstructor(); // FUN_0090fbf0

    // If the flag indicates a failure or heap allocation, clean up.
    if ((param_2 & 1) != 0) {
        internalDeallocate(this); // FUN_005c4480 - e.g., operator delete or partial destructor
    }

    return this;
}