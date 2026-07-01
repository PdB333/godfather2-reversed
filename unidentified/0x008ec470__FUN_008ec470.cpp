// FUNC_NAME: SomeObject::SomeObject
// Function address: 0x008ec470
// Role: Constructor for SomeObject. Calls base class constructor and conditionally calls a cleanup/init function based on a flag.

undefined4 __thiscall SomeObject::SomeObject(SomeObject* this, byte flag)
{
    // Call base class constructor (likely at 0x008eb650)
    FUN_008eb650();
    
    // If the lowest bit of flag is set, call an additional initialization/cleanup function
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    return this;
}