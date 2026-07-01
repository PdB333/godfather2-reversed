// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_HandleSubMenuInput
// FUNC_NAME: MenuScreen::handleInput
// Address: 0x00981690
// This function handles input actions for a menu/screen, likely the character customization screen.
// It checks the action type and performs corresponding navigation or selection.

bool __thiscall MenuScreen::handleInput(int actionId)
{
    // +0x6c: selected item index (or -1 if none)
    // +0x104: screen state (3 = customize active?)
    // +0x12d: some flag (maybe pending animation)
    // +0x60: some count or flag
    // +0x11c: another flag for special behavior
    // +0x108: sub-state for editing fields
    // +299 (0x12B): flag for "isCustomizing" (appears as char)
    // +300 (0x12C): flag for "hasChanges" (appears as char)
    
    // Global UI manager object (array-like access at indices 0x14, 0x15)
    // DAT_011304f8 is likely a pointer to a UIManager instance
    extern int* g_UIManager; // base pointer
    
    // Global path strings for screen transitions
    extern const char* g_strCharacterSelect; // DAT_011302c0
    extern const char* g_strCustomize;       // DAT_011302e8
    extern const char* g_strSaveScreen;      // DAT_01130310
    // Other globals for directional events
    extern int g_DirectionalEvent; // DAT_00d8fe44? (unused in this context?)
    // DAT_011304d8 and DAT_011301c0 are likely other strings/sounds
    
    int primaryAction = getPrimaryActionCode(); // FUN_00466840
    if (actionId == primaryAction) {
        // Submit action
        if ((*(int*)((char*)this + 0x6C) == -1) || (*(int*)((char*)this + 0x104) != 3)) {
            // Not selecting a valid item or not in customize state
            if (*(char*)((char*)this + 299) != '\0') {
                // Currently customizing: go to confirm? or finish
                g_UIManager[0x14] = 1;
                g_UIManager[0x15] = -1;
                (*(code**)(*(int*)g_UIManager + 0x28))(); // call vtable method at offset 0x28
                loadScreen("customize"); // FUN_00954890
                
                // Build path to customize screen
                char pathBuffer[12]; // local_c, local_8, local_4
                strcpy(pathBuffer, g_strCustomize); // DAT_011302e8
                pathBuffer[8] = 0;
                pathBuffer[9] = 0;
                pathBuffer[10] = 0;
                loadScreenFromPath(&pathBuffer, 0); // FUN_00408a00
                return false;
            }
        }
        else {
            // Has selected item and in customize state (state==3)
            g_UIManager[0x14] = 0;
            g_UIManager[0x15] = *(int*)((char*)this + 0x6C); // store selected item index
            (*(code**)(*(int*)g_UIManager + 0x28))();
            loadScreen("customize");
            char pathBuffer[12];
            strcpy(pathBuffer, g_strCustomize);
            pathBuffer[8] = 0;
            pathBuffer[9] = 0;
            pathBuffer[10] = 0;
            loadScreenFromPath(&pathBuffer, 0);
            return false;
        }
        // Fall through if no condition met: do nothing? Actually original code has no else after if, so returns 0.
        char pathBuffer[12];
        strcpy(pathBuffer, g_strCharacterSelect);
        pathBuffer[8] = 0;
        pathBuffer[9] = 0;
        pathBuffer[10] = 0;
        loadScreenFromPath(&pathBuffer, 0);
        return false;
    }
    
    int secondaryAction = getSecondaryActionCode(); // FUN_00466860
    if (actionId == secondaryAction) {
        // Cancel/back action
        char buffer[12];
        buffer[8] = 0;
        buffer[9] = 0;
        buffer[10] = 0;
        if (hasUnsavedChanges() != '\0') { // FUN_00957d00
            // Show save prompt
            strcpy(buffer, g_strSaveScreen); // DAT_01130310
        } else {
            strcpy(buffer, g_strCharacterSelect);
        }
        loadScreenFromPath(&buffer, 0);
        return false;
    }
    
    // Switch on other action IDs
    switch (actionId) {
    case 3:
        if (*(char*)((char*)this + 0x12D) != '\0') {
            handleSpecialAction(); // FUN_00980590
            return false;
        }
        break;
    case 5:
        if ((*(char*)((char*)this + 299) == '\0') && (*(char*)((char*)this + 300) != '\0')) {
            handleUnsavedChanges(); // FUN_009814a0
            return false;
        }
        if (*(int*)((char*)this + 0x60) == 0) {
            return false;
        }
        // fall through to case 0
    case 0:
        return true; // indicates action handled? or continue?
    case 6:
        sendDirectionalEvent("MoveLeft", &g_DirectionalEvent, &g_someSound, g_strCharacterSelect); // FUN_00929a20
        return false;
    case 7:
        sendDirectionalEvent("MoveRight", &g_DirectionalEvent, &g_someSound, g_strCharacterSelect);
        return false;
    case 8:
        sendDirectionalEvent("MoveUp", &g_DirectionalEvent, &g_someOtherParam, g_strCharacterSelect);
        return false;
    case 9:
        sendDirectionalEvent("MoveDown", &g_DirectionalEvent, &g_someOtherParam, g_strCharacterSelect);
        return false;
    case 10: // Confirm edit?
        if ((*(int*)((char*)this + 0x6C) == -1) || (*(int*)((char*)this + 0x104) != 3)) {
            if (*(int*)((char*)this + 0x11C) != 0) {
                handleSpecialEdit(); // FUN_0097f800
                return false;
            }
        } else {
            if (*(int*)((char*)this + 0x108) == 8) {
                handleEditType8(); // FUN_00980a00
                return false;
            }
            if (*(int*)((char*)this + 0x108) == 1) {
                handleEditType1(); // FUN_00980a60
                return false;
            }
        }
        // Fallback: play cancel sound
        playSound(&g_strCharacterSelect, 0); // FUN_00402050
        return false;
    case 12: // Possibly scroll
        setScrollStep((*(int*)((char*)this + 0x60) != 0) + 1, 0); // FUN_00922e20
        return false;
    }
    
    return 0; // default return value
}