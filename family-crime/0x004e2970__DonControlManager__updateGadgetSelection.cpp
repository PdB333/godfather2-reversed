// FUNC_NAME: DonControlManager::updateGadgetSelection
void DonControlManager::updateGadgetSelection() {
    uint32_t index = 0;
    do {
        // g_gadgetTable is an array of 20 entries (each 8 bytes? or just ints)
        // Compare current gadget ID with highlighted ID
        if (g_gadgetTable[index * 2] == g_highlightedItemId) {
            // If the gadget is enabled (bit 1 of flags) and within valid range
            if ((index < 0x14) && ((*(uint8_t*)(&g_gadgetFlags + index * 2) & 2) != 0)) {
                // Play sound or trigger action
                FUN_00609810();
                return;
            }
            break;
        }
        index++;
    } while (index < 0x14);

    // Update min/max selection bounds
    if (g_uiMinSelection < 0x34) {
        g_uiMinSelection = 0x34;
    }
    if (0x34 < g_uiMaxSelection) {
        g_uiMaxSelection = 0x34;
    }

    g_uiSelectionMode = 1;
    uiRefreshDisplay(3, 1, 1);

    if (g_uiMinSelection < 0x38) {
        g_uiMinSelection = 0x38;
    }
    if (0x38 < g_uiMaxSelection) {
        g_uiMaxSelection = 0x38;
    }
    g_uiGadgetPropertyA = 8;

    if (g_uiMinSelection < 0x39) {
        g_uiMinSelection = 0x39;
    }
    if (0x39 < g_uiMaxSelection) {
        g_uiMaxSelection = 0x39;
    }
    g_uiGadgetPropertyB = 0;

    if (g_uiMinSelection < 0x3a) {
        g_uiMinSelection = 0x3a;
    }
    if (0x3a < g_uiMaxSelection) {
        g_uiMaxSelection = 0x3a;
    }
    g_uiGadgetPropertyC = 0xFF;

    // Call internal update function for gadgets
    updateGadgetState();

    // Now update back to default state
    if (g_uiMinSelection < 0x34) {
        g_uiMinSelection = 0x34;
    }
    if (0x34 < g_uiMaxSelection) {
        g_uiMaxSelection = 0x34;
    }
    g_uiSelectionMode = 0;
    uiRefreshDisplay(1, 1, 1);

    if (g_uiMinSelection < 0x38) {
        g_uiMinSelection = 0x38;
    }
    if (0x38 < g_uiMaxSelection) {
        g_uiMaxSelection = 0x38;
    }
    g_uiGadgetPropertyA = 8;

    if (g_uiMinSelection < 0x39) {
        g_uiMinSelection = 0x39;
    }
    if (0x39 < g_uiMaxSelection) {
        g_uiMaxSelection = 0x39;
    }
    g_uiGadgetPropertyB = 0;

    if (g_uiMinSelection < 0x3a) {
        g_uiMinSelection = 0x3a;
    }
    if (0x3a < g_uiMaxSelection) {
        g_uiMaxSelection = 0x3a;
    }
    g_uiGadgetPropertyC = 0xFFFFFFFF;
}