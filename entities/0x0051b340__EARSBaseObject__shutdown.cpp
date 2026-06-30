// FUNC_NAME: EARSBaseObject::shutdown
void cleanupHelper(); // forward declaration of callee at 0x0051b120

class EARSBaseObject {
public:
    void shutdown();

private:
    // +0x08: pointer to a child/resource (set to zero on cleanup)
    void* m_pChild;
    // +0x0C: bitfield of state flags
    uint32_t m_flags;
};

void EARSBaseObject::shutdown() {
    // Clear bit 0 (likely "active" or "in use" flag)
    m_flags &= 0x7FFFFFFE;

    // Check bit 17 (0x20000); if not set, set it and call a global cleanup helper
    if ((m_flags & 0x20000) == 0) {
        m_flags |= 0x20000;
        cleanupHelper();
    }

    // Clear bit 18 (0x40000) – another state flag
    m_flags &= 0xFFFBFFFF;

    // If child pointer exists, zero its target and release the pointer
    if (m_pChild != nullptr) {
        *reinterpret_cast<int32_t*>(m_pChild) = 0;
        m_pChild = nullptr;
    }
}