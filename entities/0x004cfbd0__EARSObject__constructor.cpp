// FUNC_NAME: EARSObject::constructor
EARSObject * __thiscall EARSObject::constructor(EARSObject *this, byte flag)
{
    // call base class constructor (likely EARSObjectBase at 0x004cfbf0)
    EARSObjectBase::constructor();

    // if flag bit 0 is set, perform additional initialization (possibly register in system list)
    if ((flag & 1) != 0) {
        registerInSystem(this); // FUN_009c8eb0 - registers object with global manager
    }
    return this;
}