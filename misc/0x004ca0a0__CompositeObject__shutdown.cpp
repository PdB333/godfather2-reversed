// FUNC_NAME: CompositeObject::shutdown

class IManager {
public:
    virtual void releaseResource(int* resource, int flag) = 0; // vtable+0x04
    virtual void finalize() = 0;                               // vtable+0x0c
};

class CompositeObject {
public:
    IManager* m_pManager2; // +0x04
    int*      m_pResource2; // +0x08
    IManager* m_pManager1; // +0x0c
    int*      m_pResource1; // +0x10

    void shutdown();
};

// Address: 0x004ca0a0
// Called from FUN_004c9a70
// Cleans up two resource-manager pairs in reverse order.
void CompositeObject::shutdown()
{
    // First pair: resource at +0x10, manager at +0x0c
    if (m_pResource1 != nullptr) {
        m_pManager1->releaseResource(m_pResource1, 0);
        m_pResource1 = nullptr;
    }
    m_pManager1->finalize();

    // Second pair: resource at +0x08, manager at +0x04
    if (m_pResource2 != nullptr) {
        m_pManager2->releaseResource(m_pResource2, 0);
        m_pResource2 = nullptr;
    }
    m_pManager2->finalize();
}