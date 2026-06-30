// FUNC_NAME: UnknownClass::constructor
// Address: 0x0074b040
// Role: Constructor that optionally destroys the object if a certain flag is set.
//       Calls base construct, then if param_2 has bit 0 set, calls destructor+dealloc.

uint UnknownClass::constructor(byte param_2)
{
    baseConstruct(); // FUN_0074a900 - likely initializes base class or members

    if ((param_2 & 1) != 0) {
        destroyAndDeallocate(this); // FUN_00624da0 - likely destructor or delete
    }
    return this;
}