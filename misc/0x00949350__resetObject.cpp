// FUNC_NAME: resetObject
struct ResetObject {
    int m_handle; // +0x00
    int m_flags;  // +0x04
    int m_data;   // +0x08
};

void __fastcall resetObject(ResetObject* this) {
    this->m_flags = 0;
    // Release any resource held in m_handle
    FUN_009c8f10(this->m_handle);
    this->m_handle = 0;
    this->m_data = 0;
}