// FUNC_NAME: BaseEARSObject::dtor
void __fastcall BaseEARSObject::dtor(BaseEARSObject *this) // __fastcall with this as first param
{
    // Set vtable to the "destroying" vtable (pre-destruction state)
    this->vtable = &PTR_FUN_00e372b4;

    // If there is a sub-object pointer at offset +0x20 (param_1[8]), call its destructor
    if (this->subObject != 0) {
        // Calls the second slot (index 1) of a global vtable (DAT_01194538)
        // with argument 0 (i.e., complete destructor, no deallocation)
        (*(void (__thiscall **)(void *, int))((*DAT_01194538)[4]))(this->subObject, 0);
    }

    // Set vtable to the "destroyed" vtable (post-destruction state)
    this->vtable = &PTR_LAB_00e3729c;
    return;
}