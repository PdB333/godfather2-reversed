// Xbox PDB: EARS_Apt_UIHud_ShowPlayerCSA
// FUNC_NAME: Player::showPlayerCSA
void __thiscall Player::showPlayerCSA(int param_2, int param_3, int param_4) {
    char* stringPtr;
    int unused1;
    int unused2;
    void (*freeFunc)(void*);

    if (param_4 == 0) {
        // No extra data: display simple message with default text
        debugPrintf(*(int*)(this + 0xfc), 0x80, (const char*)PTR_LAB_00d78708, param_3);
    } else {
        // Load localized string from resource table (param_4 is ID)
        stringPtr = nullptr;
        unused1 = 0;
        unused2 = 0;
        freeFunc = nullptr;
        loadString(param_4, &stringPtr, 1);

        const char* displayText = (stringPtr != nullptr) ? stringPtr : (const char*)&DAT_0120546e;
        debugPrintf(*(int*)(this + 0xfc), 0x80, "#%u %s", param_3, displayText);

        if (stringPtr != nullptr) {
            freeFunc(stringPtr); // Release allocated string
        }
    }

    // Display the message on screen (likely via HUD)
    displayMessage(*(int*)(this + 0xf8), param_2, 0x80, 0);

    // Trigger the "ShowPlayerCSA" cutscene action
    triggerCSA("ShowPlayerCSA", 0, &DAT_00d8a64c, 0);

    // Set bit 0x100 in flags (+0x5c)
    *(uint32_t*)(this + 0x5c) |= 0x100;
}