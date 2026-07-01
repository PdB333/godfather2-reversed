// FUNC_NAME: UIScreen::handleMenuCommand

bool __thiscall UIScreen::handleMenuCommand(int command, int param2, int param3, int param4, int param5) {
    bool handled = true; // default to handled

    // Switch on command ID, offset by 0x23
    switch (command - 0x23) {
    case 0: { // command == 0x23
        playMenuSound(1); // e.g., menu confirm / start sound
        return true;
    }
    case 1: { // command == 0x24 (likely back/exit)
        int* pScreenData = (int*)this->field_0x5C; // +0x5C: probably m_pScreenData

        playMenuSound(1); // play sound effect

        if (pScreenData != nullptr) {
            // Get UI manager singleton at global DAT_01131040 via function
            void* uiManager = getUIManagerSingleton(/* likely global */);

            // +0x24 from that singleton: maybe a pointer to active screen controller
            int** screenController = (int**)*((int*)uiManager + 0x24 / 4);

            if (screenController != nullptr) {
                // Calculate widget offset from this->field_0x70 (m_pWidget)
                // If m_pWidget is 0, offset = 0; else offset = m_pWidget - 0x48 (base adjustment)
                int widgetOffset = (this->field_0x70 == 0) ? 0 : ((int)this->field_0x70 - 0x48);

                // Call virtual function at vtable index 12 (0x30/4) on screenController
                // This likely performs a UI transition (back/exit)
                (*(void(__thiscall**)(int))(*(int*)screenController + 0x30))(widgetOffset);
            }
        }

        // Handle animation or effect
        int animParam1 = 0;
        int animParam2 = getAnimationHandle(0, 0); // from function that returns a handle
        playAnimationByHash(0x575ebb45, 0, animParam2, animParam1); // play exit animation hash
        endAnimation(); // cleanup
        return true;
    }
    case 2: { // command == 0x25
        int* pScreenData = (int*)this->field_0x5C;
        // Check bit 10 (>> 10 & 1) at offset 0x238*4 = 0x8E0 from screen data
        if ((((uint)pScreenData[0x238] >> 10) & 1) != 0) {
            // Call virtual function at vtable index 0x98 (0x260/4) on screen data
            (*(void(__thiscall**)(void))((int*)pScreenData[0])[0x260])(); // likely close/hide
            return true;
        }
        // fall through to default if condition false
        break;
    }
    case 3: { // command == 0x26
        int* pWidget = (int*)this->field_0x70; // m_pWidget
        if (pWidget != nullptr && pWidget != (int*)0x48) {
            int widgetBase = (pWidget == (int*)0) ? 0 : ((int)pWidget - 0x48);
            // Check a flag at offset 0x1B8C from widget base
            if (*(char*)(widgetBase + 0x1B8C) != '\0') {
                // Play confirm animation
                (*(void(__thiscall**)(uint, int, int, int, float, float))this->vtable[0x2c/4])(0x62a76a81, 1, 1, 0, 1.0f, 1.0f);
            } else {
                // Play cancel animation
                (*(void(__thiscall**)(uint, int, int, int, float, float))this->vtable[0x2c/4])(0x2077f987, 1, 1, 0, 1.0f, 1.0f);
            }
            return true;
        }
        break;
    }
    default: {
        handled = handleDefaultCommand(command, param2, param3, param4, param5);
        break;
    }
    }
    return handled;
}