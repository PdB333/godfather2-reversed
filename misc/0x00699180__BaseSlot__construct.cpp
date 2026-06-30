// FUNC_NAME: BaseSlot::construct
void __thiscall BaseSlot::construct(BaseSlot* this)
{
    this->m_field0 = 0;              // +0x00
    this->m_field4 = 0;              // +0x04
    this->m_field8 = 0;              // +0x08
    this->m_fieldC = 0;              // +0x0C
    this->m_field18 = 0xFFFFFFFF;    // +0x18: parent or index, default -1
    this->m_field1C = 0;             // +0x1C
    this->m_field20 = 1;             // +0x20: active/enabled flag
    this->m_field24 = 0;             // +0x24
    this->m_field28 = 0;             // +0x28
    this->m_field2C = 0;             // +0x2C
    this->m_field30 = 0;             // +0x30
    this->m_field34 = 0;             // +0x34
    // Note: fields at +0x10 and +0x14 are not initialized by this constructor
}