// FUNC_NAME: BufferManager::BufferManager
void __thiscall BufferManager::BufferManager(uint size, uint initialValue) {
    // vtable pointer
    this->vtable = (void*)&BufferManager_vtable;
    // store initial value passed in EAX (reserved)
    this->m_initialValue = initialValue;
    // initialize two slots (likely counters)
    this->m_field2 = 0;
    this->m_field3 = 0;
    // store the global pointer
    gBufferManager = this;
    // more counters
    this->m_field4 = 0;
    this->m_field5 = 0;
    // allocate a buffer of size (size * 4) with overflow safety
    this->m_buffer = (uint*)allocateMemory((uint)((unsigned long long)size * 4 >> 32) != 0 ? 0xFFFFFFFF : (size * 4));
    // store the requested element count
    this->m_elementCount = size;
    // two more slots (maybe head/tail indices)
    this->m_field8 = 0;
    this->m_field9 = 0;
    // initialize a critical section at offset +0x28
    InitializeCriticalSection((LPCRITICAL_SECTION)(&this->m_criticalSection1));
    // clear a block of 8 uint slots (offset +0x48 to +0x5C)
    this->m_field0x12 = 0;
    this->m_field0x13 = 0;
    this->m_field0x14 = 0;
    this->m_field0x15 = 0;
    this->m_field0x16 = 0;
    this->m_field0x17 = 0;
    this->m_field0x18 = 0;
    *(uint8*)(&this->m_field0x19) = 0; // single byte set to 0
    // initialize a second critical section at offset +0x68
    InitializeCriticalSection((LPCRITICAL_SECTION)(&this->m_criticalSection2));
    // clear another block (offset +0x88 to +0x94)
    this->m_field0x22 = 0;
    this->m_field0x23 = 0;
    this->m_field0x24 = 0;
    this->m_field0x25 = 0;
}