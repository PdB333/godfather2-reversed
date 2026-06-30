// FUNC_NAME: Handle::Reset
// Function address: 0x006f9020
// Role: Releases external resource and zeroes all handle fields
struct Handle {
    int m_resource; // +0x00
    int m_flags;    // +0x04
    int m_data;     // +0x08

    void Reset(); // __fastcall
};

void Handle::Reset() {
    m_flags = 0;
    FUN_009c8f10(m_resource); // Release external resource
    m_resource = 0;
    m_data = 0;
}