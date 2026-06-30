// FUNC_NAME: ResourceHolder::reset

extern "C" void ReleaseResource(void *pResource);  // address 0x009c8f10 - frees or releases the resource pointer

class ResourceHolder {
public:
    void *m_pResource; // +0x00
    int m_nCount;      // +0x04
    int m_nFlags;      // +0x08

    void reset() {
        m_nCount = 0;
        ReleaseResource(m_pResource);
        m_pResource = nullptr;
        m_nFlags = 0;
    }
};