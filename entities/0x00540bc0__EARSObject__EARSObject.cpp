// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject* this, int param2, int param3, int param4, int param5)
{
    // +0x00: object type identifier (0x3e0 = 992)
    this->m_objectType = 0x3e0;
    // +0x04: first data field
    this->m_field1 = param2;
    // +0x08: second data field
    this->m_field2 = param3;
    // +0x0C: third data field
    this->m_field3 = param4;
    // +0x10: fourth data field
    this->m_field4 = param5;
}