// FUNC_NAME: ActionBase::stop
class ActionBase {
public:
    // +0x1c: bitflags; bit 1 (0x2) indicates stop requested
    uint32_t m_flags;
    // +0x20: pointer to a sub-action (e.g., current active action)
    ActionBase* m_pSubAction;

    void __thiscall stop() {
        m_flags |= 2; // Set the stop flag
        if (m_pSubAction != nullptr) {
            m_pSubAction->stop(); // Recursively stop sub-action
        }
    }
};