// FUNC_NAME: GenericObject::~GenericObject
void __thiscall GenericObject::~GenericObject(GenericObject* this)
{
    // Release child object at offset +0x10
    if (this->m_pChildOne != 0) {
        FUN_009c8f10(this->m_pChildOne);
    }
    // Release child object at offset +0x8 (function also clears the pointer)
    if (this->m_pChildTwo != 0) {
        FUN_004daf90(&this->m_pChildTwo);
    }
}