// FUNC_NAME: UIButtonManager::handleButtonEvent
char __thiscall UIButtonManager::handleButtonEvent(int this, const char* input) {
    char matchedButton = '\0';
    uint i = 0;

    // Check if input matches one of the 4 predefined rollover button names
    do {
        if (i > 3) break;
        const char* rolloverName = *reinterpret_cast<const char**>(&g_rolloverButtonNames + i);
        const char* pInput = input;
        do {
            char cRoll = *rolloverName;
            char cInput = *pInput;
            if (cRoll != cInput) {
                int cmp = (cRoll < cInput) ? -1 : 1;
                goto check_cmp;
            }
            if (cRoll == '\0') break;
            cRoll = rolloverName[1];
            cInput = pInput[1];
            if (cRoll != cInput) {
                cmp = (cRoll < cInput) ? -1 : 1;
                goto check_cmp;
            }
            rolloverName += 2;
            pInput += 2;
        } while (*rolloverName != '\0');
        cmp = 0;
check_cmp:
        if (cmp == 0) {
            UIEventDispatcher::dispatch("RollOverButton", 0, g_uiDispatcher, 1, g_rolloverPath);
            matchedButton = '\x01';
        }
        i += 4;
    } while (!matchedButton);

    // Check if input matches one of the 12 item hotspots
    for (uint j = 0; j < 12; j++) {
        char hotspotPath[64];
        formatPath(hotspotPath, 64, "/finl/mcMain/content_mc/titles/item%d/hotspot", j);
        if (strncmp(input, hotspotPath, 64) == 0) {
            UIEventDispatcher::dispatch("UnhighlightSelected", 0, g_uiDispatcher, 0);
            *reinterpret_cast<uint*>(this + 0x154) = j;  // +0x154: current selected index
            UIEventDispatcher::dispatch("HighlightSelected", 0, g_uiDispatcher, 0);
        }
    }

    return matchedButton;
}