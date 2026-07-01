// FUNC_NAME: ResourceHandle::reset
void ResourceHandle::reset() {
    m_field4 = 0;                        // offset 0x04, some counter/state
    FUN_009c8f10(m_ptr);                  // release/cleanup handle at offset 0x00
    m_ptr = 0;                           // offset 0x00, pointer/resource
    m_field8 = 0;                        // offset 0x08, another flag/counter
}