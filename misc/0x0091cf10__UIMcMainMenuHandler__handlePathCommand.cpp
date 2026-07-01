// FUNC_NAME: UIMcMainMenuHandler::handlePathCommand
// Function address: 0x0091cf10
// Role: Handles UI navigation commands for the McMain screen, processing path strings to switch between sections (Overview, Game Modes, Specialties, Combat) and button interactions.

bool __thiscall UIMcMainMenuHandler::handlePathCommand(int thisPtr, const char* path)
{
    char fullPath[64]; // 0x40 bytes (local_40)
    bool bVar6, bVar7;
    int iVar3;
    int unused; // iVar3 reused, but result of comparison often stored here
    void* soundHandle;
    const char* actionStr;

    // Build path: /comm/mcMain/content_mc/item%d/item_hspt where %d = itemId at +0xB4
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/item_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        // Item path matched
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/overallRow_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/overallRow_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/gameModesRow_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/gameModesRow_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_17_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_17_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_18_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_18_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_19_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_19_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_20_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_20_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_21_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_21_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_22_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_22_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/speciality_23_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/speciality_23_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Build path: /comm/mcMain/content_mc/item%d/combatRow_hspt
    buildPathString(fullPath, "/comm/mcMain/content_mc/item%d/combatRow_hspt", *(int*)(thisPtr + 0xB4));
    if (strCompare(fullPath, path) == 0) {
        soundHandle = getUISoundManager();
        playUISound(soundHandle);
        return true;
    }

    // Check for button_0 path
    if (strCompareN("/comm/buttons/button_0/button", path, 30) == 0) {
        soundHandle = getUISoundManager2(); // alternative sound? (FUN_00466860)
        playUISound(soundHandle);
        return true;
    }

    // Check for button_2 path
    if (strCompareN("/comm/buttons/button_2/button", path, 30) == 0) {
        playMenuSound(0xC); // 0xC sound index
        return true;
    }

    // Check for section paths
    if (strCompareN("/comm/mcMain/content_mc/bg/section_0/section_hspt", path, 50) == 0) {
        int curSection = *(int*)(thisPtr + 0xB8); // +0xB8 current section index
        if (curSection == 10 || curSection == 11 || curSection == 12) {
            // Already on Overview section
            return true;
        }
        setCurrentSection(10); // FUN_00918110
        actionStr = "ShowOverall";
        goto executeAction;
    }

    if (strCompareN("/comm/mcMain/content_mc/bg/section_1/section_hspt", path, 50) == 0) {
        int curSection = *(int*)(thisPtr + 0xB8);
        if (curSection >= 13 && curSection <= 17) { // covers 0xD, 0xE, 0xF, 0x10, 0x11
            return true;
        }
        setCurrentSection(13); // 0xD
        actionStr = "ShowGameModes";
        goto executeAction;
    }

    if (strCompareN("/comm/mcMain/content_mc/bg/section_2/section_hspt", path, 50) == 0) {
        int curSection = *(int*)(thisPtr + 0xB8);
        if (curSection >= 18 && curSection <= 24) { // 0x12 to 0x18
            return true;
        }
        setCurrentSection(19); // 0x13
        actionStr = "ShowSpecialty";
        goto executeAction;
    }

    if (strCompareN("/comm/mcMain/content_mc/bg/section_3/section_hspt", path, 50) == 0) {
        int curSection = *(int*)(thisPtr + 0xB8);
        if (curSection == 25) { // 0x19
            return true;
        }
        setCurrentSection(25);
        actionStr = "ShowCombat";
        goto executeAction;
    }

    // Check selector arrows
    if (strCompareN("/comm/mcMain/content_mc/titles/selector/selector_left", path, 54) == 0) {
        playMenuSound(3); // left arrow sound
        return true;
    }

    if (strCompareN("/comm/mcMain/content_mc/titles/selector/selector_right", path, 55) == 0) {
        playMenuSound(5); // right arrow sound
        return true;
    }

    // No match
    return false;

executeAction:
    // FUN_005a04a0: likely sends string command to Lua/UI
    sendUICallback(actionStr, 0, (const char*)0x00d8510c, 0);
    // FUN_0091cd80: UI state change (parameter 1,0)
    updateUIVisibility(1, 0);
    // FUN_00402050: Set some global flag (maybe input mode)
    setUIInteractionMode(0);
    return true;
}