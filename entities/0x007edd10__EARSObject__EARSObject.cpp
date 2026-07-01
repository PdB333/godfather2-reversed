// FUNC_NAME: EARSObject::EARSObject
undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte flags)
{
    // Call base class constructor (FUN_007edb30)
    EARSObject::baseConstructor(this); 
    // If the lowest bit of flags is set, perform cleanup (likely deallocation or finalization)
    if ((flags & 1) != 0) {
        EARSObject::cleanup(this); // FUN_009c8eb0 - possibly free memory or destruct resources
    }
    return this;
}