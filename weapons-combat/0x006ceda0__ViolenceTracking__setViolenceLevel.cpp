// FUNC_NAME: ViolenceTracking::setViolenceLevel
// Address: 0x006ceda0
// Sets violence level: 0=none, 1=low, 2=high (clamped from input)
void __thiscall ViolenceTracking::setViolenceLevel(int level) {
    if (level == 0) {
        this->m_violenceLevel = 0; // +0xC4
        return;
    }
    // Clamp any value >1 to 2; only level=1 maps to 1
    this->m_violenceLevel = (level != 1) + 1; // +0xC4
}