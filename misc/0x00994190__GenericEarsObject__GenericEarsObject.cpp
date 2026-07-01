// FUNC_NAME: GenericEarsObject::GenericEarsObject
// Address: 0x00994190
// Constructor for GenericEarsObject. Calls base constructor, then if initFlag has bit 0 set, performs additional initialization.
GenericEarsObject* __thiscall GenericEarsObject::GenericEarsObject(GenericEarsObject* this, byte initFlag)
{
    // Base class constructor (likely EARS object base)
    EarsObjectBase::EarsObjectBase(this);
    if (initFlag & 1)
    {
        // Additional initialization – may allocate or set up internal structures
        finalizeConstruction(this); // FUN_005c4480
    }
    return this;
}