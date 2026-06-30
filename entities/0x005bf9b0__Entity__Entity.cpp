// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(Entity* this)
{
    this->m_someId = -1;                          // +0x04: default ID (-1)
    this->m_flag1 = 1;                            // +0x08: some boolean flag
    this->m_byteFlag = 1;                         // +0x0C: single byte flag
    this->m_vtable2 = &s_vtable2;                 // +0x10: first vtable pointer (overwritten later)
    this->m_counter = 0;                          // +0x1C: some counter
    this->m_value1 = 0;                           // +0x14: value field
    this->m_value2 = 0;                           // +0x18: another value
    this->vfptr = &s_vtable1;                     // +0x00: main vtable pointer
    this->m_vtable2 = &s_vtable3;                 // +0x10: second vtable pointer (overwrites first)
    this->m_anotherCounter = 0;                   // +0x30: additional counter
    this->m_field28 = 0;                          // +0x28: unknown
    this->m_field2C = 0;                          // +0x2C: unknown
    this->m_field34 = 0;                          // +0x34: unknown
    this->m_timeoutMs = 1000;                     // +0x38: default timeout (1000ms)
    this->m_timeoutEnabled = 1;                   // +0x3C: byte – timeout enabled
    this->m_field40 = 0;                          // +0x40: zeroed
    this->m_field44 = 0;                          // +0x44: zeroed
    this->m_field48 = 0;                          // +0x48: byte
    this->m_field49 = 1;                          // +0x49: byte – set to 1
    this->m_field4A = 0;                          // +0x4A: short – zeroed
}