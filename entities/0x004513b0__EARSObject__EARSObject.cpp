// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004513b0
// Role: Constructor for EARSObject base class; optionally registers the object in a global list.

EARSObject::EARSObject(bool registerObject /* +0x0: byte parameter */)
{
    // Call base class constructor (at 0x004513e0)
    // This likely initializes vtable pointer and basic fields.
    FUN_004513e0();

    // If register flag is set, register this object (e.g., add to global object manager)
    if (registerObject)
    {
        FUN_009c8eb0(this); // Registration function
    }
}