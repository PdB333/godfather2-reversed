// FUNC_NAME: ExampleObject::reset
// Function address: 0x0092db00
// Role: Reset object state – release handle, zero fields.

struct ExampleObject {
    int m_handle; // +0x00
    int m_flag;   // +0x04
    int m_other;  // +0x08
};

void __thiscall ExampleObject::reset(ExampleObject* this) {
    this->m_flag = 0;
    releaseHandle(this->m_handle); // calls FUN_009c8f10
    this->m_handle = 0;
    this->m_other = 0;
}