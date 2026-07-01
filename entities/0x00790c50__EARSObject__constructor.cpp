// FUNC_NAME: EARSObject::constructor
EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte initFlags)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    // FUN_00790410 - base initialization
    Object::constructor(this);

    // If the lowest bit of initFlags is set, perform additional initialization
    // with size 0xe0 (224 bytes) - possibly allocate or initialize a sub-object
    if (initFlags & 1)
    {
        // FUN_0043b960 - initializes a member array or allocates memory of size 0xe0
        // The second parameter 0xe0 might be a size or type identifier
        this->initSubObject(0xe0);
    }

    return this;
}