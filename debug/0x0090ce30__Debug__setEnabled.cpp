// FUNC_NAME: Debug::setEnabled
// Function address: 0x0090ce30
// Sets the debug enabled flag and updates the internal flags field at offset 0x14.

char g_debugEnabled = 0; // global DAT_0112a7a5

class Debug {
public:
    uint32_t m_flags; // +0x14 (bitfield: bit 2 = enabled flag)
    // ... other members
};

void __thiscall Debug::setEnabled(char enabled) {
    g_debugEnabled = enabled;
    if (enabled) {
        m_flags |= 0x4;
    } else {
        m_flags &= ~0x4;
    }
}