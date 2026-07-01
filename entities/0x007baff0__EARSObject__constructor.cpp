//FUNC_NAME: EARSObject::constructor
EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte flags)
{
    // Call base constructor or initialization routine
    FUN_007ba0d0();  // Likely this->init() or base class constructor

    // If the low bit of flags is set, delete this object (placement delete)
    if ((flags & 1) != 0) {
        FUN_00624da0(this);  // operator delete or destructor
    }

    return this;
}