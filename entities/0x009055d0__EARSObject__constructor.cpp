// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte flags)
{
    // Initialize base class / internal state
    this->init();

    // If the placement destruction flag is set, destroy the object
    // (common pattern for placement new / cleanup on allocation failure)
    if ((flags & 1) != 0) {
        this->destroy();
    }

    return this;
}