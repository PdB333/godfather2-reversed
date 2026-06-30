// FUNC_NAME: EARSObject::release
int __thiscall EARSObject::release(EARSObject* this, byte deleteFlag)
{
    // If there is an internal object, call its destructor via a function pointer at +0x18
    if (*(void**)(this + 0x0C) != 0) {
        (*(void(__thiscall**)(void*))(this + 0x18))(*(void**)(this + 0x0C));
    }
    // If deleteFlag bit 0 is set, deallocate this object
    if ((deleteFlag & 1) != 0) {
        operator delete(this);
    }
    return this;
}