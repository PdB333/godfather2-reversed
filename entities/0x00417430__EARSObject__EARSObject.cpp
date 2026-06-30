// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject *this, uint data1, uint data2)
{
    this->vtable = &g_EARSObjectVTable; // +0x00 vtable pointer
    this->field04 = data1;              // +0x04 first data field
    this->field08 = data2;              // +0x08 second data field
}