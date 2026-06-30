// FUNC_NAME: EARSObject::EARSObject
// Address: 0x0049c610 - Base constructor for EARS engine objects. Initializes vtable and a flag at +0x04.
void __fastcall EARSObject::EARSObject(EARSObject* this)
{
    this->vtable = (void**)(0x00e3522c); // Set vtable pointer (class virtual dispatch table)
    this->mFlags = 0;                    // +0x04: Initialize flags/next pointer to 0
}