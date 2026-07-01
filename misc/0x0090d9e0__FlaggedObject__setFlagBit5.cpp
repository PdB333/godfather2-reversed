// FUNC_NAME: FlaggedObject::setFlagBit5
class FlaggedObject {
public:
    uint32_t m_flags;                              // +0x0
    // Some padding or other members between +0x4 and +0x38
    union {
        void (*m_simpleCallback)(int state);        // +0x38 (function pointer)
        intptr_t m_callbackContext;                 // +0x38 (if memberCallback used)
    };
    void (*m_memberCallback)(intptr_t* context);   // +0x4C (member function pointer)
    // size: at least 0x50

    // Sets bit 5 (0x20) of m_flags and triggers notification
    void setFlagBit5(bool enable) {
        if (enable)
            m_flags |= 0x20;
        else
            m_flags &= ~0x20;

        // If either a member callback or a simple callback is registered
        if (m_memberCallback != nullptr || m_simpleCallback != nullptr) {
            if (m_memberCallback != nullptr) {
                // Pass pointer to the context field (offset +0x38) to the member callback
                m_memberCallback(&m_callbackContext);
            } else {
                // Simple callback: pass 1 (disable) or 2 (enable)
                m_simpleCallback(enable ? 2 : 1);
            }
        }
    }
};