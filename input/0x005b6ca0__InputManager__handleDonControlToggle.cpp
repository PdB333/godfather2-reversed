// FUNC_NAME: InputManager::handleDonControlToggle
int InputManager::handleDonControlToggle() {
    uint* inputState = GetInputState(); // returns pointer to current controller state (likely 0x2 bytes per slot)
    uint uVar2 = *inputState & 0x7FFF; // lower 15 bits – button combination or axis value
    if ((*inputState & 0x8000) != 0 && (uVar2 == 0xD || uVar2 == 0x12)) {
        // 0x8000 flags a specific trigger (e.g., hold state), 0xD (13) and 0x12 (18) are don‑control activation combos
        DonControlManager* mgr = GetDonControlManager();
        // +0x14 holds UI flags (bit 24 = don control gadget visible)
        mgr->field_0x14 &= 0xFEFFFFFF; // clear bit 24 – hide don control gadget
    }
    return g_donControlToggleReturn; // global bool or enum, returns previous state
}