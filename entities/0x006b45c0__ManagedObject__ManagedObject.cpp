// FUNC_NAME: ManagedObject::ManagedObject
// Description: Constructor for a managed object. Calls base initializer, and optionally registers the object if param_2 bit 0 is set.

undefined4 __thiscall ManagedObject::ManagedObject(ManagedObject* this, byte param_2)
{
    // Call base class initialization (likely a base constructor or Init function)
    FUN_006b3930();

    // If the low bit of param_2 is set, register this object (e.g., add to manager lists)
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(this);
    }

    // Return this pointer, typical for C++ constructors (though usually void return)
    return (undefined4)this;
}