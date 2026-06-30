// FUNC_NAME: EARSObject::EARSObject (constructor with subobject creation flag)
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte createSubObjectFlag)
{
    // Call base class constructor (FUN_004895f0 - presumably EAObject base init)
    baseConstructor();

    // If the low bit of the flag is set, create an internal subobject
    if ((createSubObjectFlag & 1) != 0)
    {
        createSubObject(this);   // FUN_009c8eb0: allocate/init subobject (e.g., reference counter)
    }

    return this;
}