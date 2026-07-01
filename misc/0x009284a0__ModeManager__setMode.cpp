// FUNC_NAME: ModeManager::setMode

void __thiscall ModeManager::setMode(char newMode)
{
    // Check if mode actually changed (offset +0x7c stores current mode)
    if (m_mode != newMode) {
        m_mode = newMode; // +0x7c: current mode (char)
        // Broadcast "ModeChanged" event with some global payload
        notifyEvent("ModeChanged", 0, &DAT_00d87b2c, 0);
    }
}