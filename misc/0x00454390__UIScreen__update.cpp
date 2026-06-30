// FUNC_NAME: UIScreen::update
void UIScreen::update() {
    // Global: current active screen pointer
    if ((g_pActiveScreen != this) && (this->field_8 == 0)) {
        return;
    }

    int* pChild = reinterpret_cast<int*>(this->field_C);
    if (pChild != nullptr) {
        // Clear child's +0x40 field (maybe a flag or timer)
        pChild[0x10] = 0; // offset 0x40 / 4

        // Check bit 1 of child's flags at +0x30
        if (((pChild[0xC] >> 1) & 1) == 0) { // field +0x30
            if (g_bUIActive == 0) {
                goto skipActiveUpdate;
            }
            // Child state requires special handling (e.g., transition)
            onChildUpdate(); // FUN_00454030
        }
    }

    if (g_bUIActive != 0) {
        processInputForScreen(this); // FUN_00454910
    }

skipActiveUpdate:
    screenPostUpdate(); // FUN_00454e20
    return;
}