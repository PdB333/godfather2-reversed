// FUNC_NAME: SlotContainer::releaseAll
class SlotContainer {
private:
    void* m_slots[4]; // +0x4: array of 4 pointers
    void* m_pManager; // +0x14: pointer to manager with vtable
public:
    void releaseAll() {
        if (m_pManager != nullptr) {
            for (int i = 0; i < 4; ++i) {
                if (m_slots[i] != nullptr) {
                    // Call virtual release function (vtable+4)
                    (*(void (**)(void*, int))(*(void**)m_pManager + 4))(m_slots[i], 0);
                    m_slots[i] = nullptr;
                }
            }
            // Call virtual cleanup function (vtable+0xC)
            (*(void (**)(void))(*(void**)m_pManager + 0xC))();
            m_pManager = nullptr;
        }
    }
};