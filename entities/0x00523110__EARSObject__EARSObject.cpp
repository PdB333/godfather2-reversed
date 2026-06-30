// FUNC_NAME: EARSObject::EARSObject
EARSObject* __thiscall EARSObject::EARSObject(byte creationFlags) {
    // Base class constructor (FUN_005231b0)
    EARSObjectBase::EARSObjectBase();
    // If creationFlags bit 0 is set, perform extra initialization
    if ((creationFlags & 1) != 0) {
        this->initExtra();  // FUN_009c8eb0
    }
    return this;
}