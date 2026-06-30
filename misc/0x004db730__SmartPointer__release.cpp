// FUNC_NAME: SmartPointer::release
// Address: 0x004db730
// Releases the owned pointer by calling the stored deleter, then zeros all fields.

struct SmartPointer {
    void* m_ptr;                  // +0x00
    int m_field1;                 // +0x04
    int m_field2;                 // +0x08
    void (*m_deleter)(void*);     // +0x0C
};

void __thiscall SmartPointer::release() {
    if (m_ptr != nullptr) {
        m_deleter(m_ptr);
    }
    m_ptr = nullptr;
    m_field1 = 0;
    m_field2 = 0;
}