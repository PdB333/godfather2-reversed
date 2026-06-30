// FUNC_NAME: EARSObject::constructor
EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte flag) {
    // Call base class constructor or initialization routine
    baseConstructor();
    // If flag's low bit is set, deallocate/delete this object (likely memory management flag)
    if ((flag & 1) != 0) {
        operatorDelete(this);
    }
    return this;
}