// FUNC_NAME: CStepCounter::Advance
// Address: 0x004ba9f0
// Role: Increments a step counter and resets when reaching the limit, optionally clearing the limit pointer.

struct SCounterLimits {
    uint32_t m_nMaxCount; // +0x08 relative to SCounterLimits base
};

class CStepCounter {
public:
    int m_nCurrentStep;       // +0x04
    SCounterLimits* m_pLimits; // +0x08

    void __thiscall Advance();
};

void CStepCounter::Advance() {
    if (m_pLimits != nullptr) {
        m_nCurrentStep++;
        if ((uint32_t)m_nCurrentStep >= m_pLimits->m_nMaxCount) {
            m_nCurrentStep = 0;
            m_pLimits = nullptr;
        }
    }
}