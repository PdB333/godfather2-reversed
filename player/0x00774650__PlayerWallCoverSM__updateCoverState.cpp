// FUNC_NAME: PlayerWallCoverSM::updateCoverState
// Function at 0x00774650: Updates cover state machine based on player flags.
// States: 0 = eCoverNone, 1 = eCoverActive, 2 = eCoverLeaving
// Player flags (at Player+0xF4): bit2 = eFlag_LeaveCover, bit3 = eFlag_EnterCover, bit4 = eFlag_LeavingCover

class PlayerWallCoverSM {
public:
    // +0x7c: Pointer to Player subcomponent (e.g., PlayerCCTVariables) located at Player+0x48
    void* m_pSubComponent; 
    // +0x88: Current cover state
    int m_coverState; // 0,1,2

    void updateCoverState() {
        int base;
        uint32_t flags;
        int newState;

        int currentState = m_coverState;
        if (currentState == 0) {
            // State eCoverNone: check if entering cover flag (bit3)
            base = (m_pSubComponent != 0) ? (uint32_t)m_pSubComponent - 0x48 : 0;
            if (base != 0) {
                flags = *(uint32_t*)(base + 0xF4);
                // bit3 = 0x8
                if (flags & 0x8) {
                    // Transition to eCoverActive
                    m_coverState = 1; // eCoverActive
                    return;
                }
            }
            // Check if leaving cover flag (bit4)
            base = (m_pSubComponent != 0) ? (uint32_t)m_pSubComponent - 0x48 : 0;
            if (base != 0) {
                flags = *(uint32_t*)(base + 0xF4);
                if (flags & 0x10) { // bit4
                    // Transition to eCoverLeaving
                    m_coverState = 2; // eCoverLeaving
                    return;
                }
            }
        }
        else if (currentState == 1) {
            // State eCoverActive: check if should leave (bit4)
            base = (m_pSubComponent != 0) ? (uint32_t)m_pSubComponent - 0x48 : 0;
            if (base != 0) {
                flags = *(uint32_t*)(base + 0xF4);
                if (flags & 0x10) {
                    m_coverState = 2; // eCoverLeaving
                    return;
                }
            }
            // Check if should return to none (bit2)
            base = (m_pSubComponent != 0) ? (uint32_t)m_pSubComponent - 0x48 : 0;
            if (base != 0) {
                flags = *(uint32_t*)(base + 0xF4);
                if (flags & 0x4) { // bit2
                    m_coverState = 0; // eCoverNone
                    // (no return needed, will return after)
                }
            }
        }
        else if (currentState == 2) {
            // State eCoverLeaving: check if should stop leaving (bit2)
            base = (m_pSubComponent != 0) ? (uint32_t)m_pSubComponent - 0x48 : 0;
            if (base != 0) {
                flags = *(uint32_t*)(base + 0xF4);
                if (flags & 0x4) {
                    m_coverState = 0; // eCoverNone
                    return;
                }
            }
            // Check if should go back to active (bit3)
            base = (m_pSubComponent != 0) ? (uint32_t)m_pSubComponent - 0x48 : 0;
            if (base != 0) {
                flags = *(uint32_t*)(base + 0xF4);
                if (flags & 0x8) {
                    m_coverState = 1; // eCoverActive
                }
            }
        }
    }
};