// FUNC_NAME: ResourceHolder::releaseComponents
// Address: 0x00621f80
// Releases two owned sub-objects through their respective manager interfaces and calls cleanup on each manager.
// Assumed layout: this+0x4=ptr to manager2, this+0x8=child2, this+0xc=ptr to manager1, this+0x10=child1

struct IResourceManager {
    virtual void __thiscall release(void* obj, int flag) = 0;  // vtable offset +0x04
    virtual void __thiscall cleanup() = 0;                      // vtable offset +0x0c
};

struct ResourceHolder {
    // unknown vtable at +0x00
    IResourceManager* m_pManager2;   // +0x04
    void* m_pChild2;                 // +0x08
    IResourceManager* m_pManager1;   // +0x0c
    void* m_pChild1;                 // +0x10
};

void __thiscall ResourceHolder::releaseComponents() {
    // Release child1 using manager1's release (second vtable entry)
    if (m_pChild1 != 0) {
        m_pManager1->release(m_pChild1, 0);
        m_pChild1 = 0;
    }
    // Call cleanup on manager1 (fourth vtable entry)
    m_pManager1->cleanup();

    // Release child2 using manager2's release
    if (m_pChild2 != 0) {
        m_pManager2->release(m_pChild2, 0);
        m_pChild2 = 0;
    }
    // Call cleanup on manager2
    m_pManager2->cleanup();
}