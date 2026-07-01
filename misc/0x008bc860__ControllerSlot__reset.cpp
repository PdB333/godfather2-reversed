// FUNC_NAME: ControllerSlot::reset
void __fastcall ControllerSlot::reset()
{
    // +0x04: Handle/index for the controller slot
    m_handle = 0;
    // Release the input state object (XInput state) before clearing pointer
    releaseInputState(m_pInputState);
    // +0x00: Pointer to input state (XInputState*)
    m_pInputState = nullptr;
    // +0x08: Flags or additional slot data
    m_flags = 0;
}