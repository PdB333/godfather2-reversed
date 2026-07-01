// FUNC_NAME: UIManager::updateVisibility
void __fastcall UIManager::updateVisibility() {
    // Check two flag fields at +0x970 and +0x974 for bit 4 (0x10)
    bool visible = false;
    if (((*(uint*)(this + 0x970) >> 4) & 1) && ((*(uint*)(this + 0x974) >> 4) & 1)) {
        visible = true;
    }

    // Array of 22 elements starting at +0xb80, each 0x30 bytes
    // Each element is likely a UI marker or similar object
    for (int i = 0; i < 22; i++) {
        setElementVisible(this + 0xb80 + i * 0x30, visible);
    }
}