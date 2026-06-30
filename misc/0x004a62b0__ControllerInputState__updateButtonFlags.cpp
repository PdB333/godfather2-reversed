// FUNC_NAME: ControllerInputState::updateButtonFlags
void ControllerInputState::updateButtonFlags() {
    // this is an instance of ControllerInputState
    // m_pDevice: +0x00 (IInputDevice*)
    // m_buttonFlags: +0x04 (unsigned short)
    if (m_pDevice != nullptr) {
        if (m_pDevice->isUp()) {
            m_buttonFlags |= 0x8;   // bit 3 – up direction flag
        }
        if (m_pDevice->isDown()) {
            m_buttonFlags |= 0x10;  // bit 4 – down direction flag
        }
        if (m_pDevice->isLeft()) {
            m_buttonFlags |= 0x20;  // bit 5 – left direction flag
        }
        if (m_pDevice->isRight()) {
            m_buttonFlags |= 0x100; // bit 8 – right direction flag
        }
        if (m_pDevice->isButtonA()) {
            m_buttonFlags |= 0x200; // bit 9 – button A flag
        }
        if (m_pDevice->isButtonB()) {
            m_buttonFlags |= 0x400; // bit 10 – button B flag
        }
        if (m_pDevice->isButtonX()) {
            m_buttonFlags |= 0x800; // bit 11 – button X flag
        }
    }
}