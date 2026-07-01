// FUNC_NAME: UIManager::updateScreen
// Address: 0x0091e630
// This function manages the main screen/menu state machine.
// It handles initial loading (case 0), main menu display (case 1),
// and in-game sub-menu rendering (states 0x0A-0x19).
// It uses Lua script callbacks (“ShowMenu”, “HighlightSelected”) and 
// virtual function calls on the active UI component.

void UIManager::updateScreen()
{
    char isActive;
    uint count;
    int* pComponent;
    int state;
    undefined4* pTextArray;
    undefined8 result;
    char* textStr;
    undefined4 stackVar;

    // Global screen manager pointer (e.g. ScreenManager* gScreenMgr)
    int* pGlobalMgr = (int*)0x01223484;

    state = *(int*)(this + 0xB8);          // +0xB8: m_currentState

    switch (state)
    {
    case 0:                               // Initial state – load resources
        loadInitialMenu();                 // FUN_0091e210
        return;

    case 1:                               // Main menu state
        if (gInputManager != 0)           // DAT_01130044
        {
            count = *(int*)(gInputManager + 0xC0) + *(int*)(gInputManager + 0xB4);
            if (count < *(uint*)(this + 0xA0))   // +0xA0: m_menuItemCount?
            {
                pComponent = *(int**)(*(int*)(this + 0x9C) + count * 4); // +0x9C: m_menuItems
                if (*pComponent == 8)      // Component type 8 = scriptable menu item
                {
                    // Call a virtual function on the component to get a value
                    result = (**(code**)(*(int*)pComponent[2] + 8))(); // vcall +8
                    // Store result into global manager at offset 0x28
                    *(undefined8*)(pGlobalMgr + 0x28) = result;

                    // Prepare Lua callback data
                    stackVar = 0;
                    textStr = "ShowMenu";
                    // Call Lua: showMainMenu()
                    Lua_callFunction("ShowMenu", 0, &DAT_00d8510c, 0); // FUN_005a04a0
                    // Call Lua: highlightFirstItem()
                    Lua_callFunction("HighlightSelected", 0, &DAT_00d8510c, 0);
                    refreshMenuUI();        // FUN_00919730
                    return;
                }
            }
        }
        return;

    default:                             // States outside 10-0x19 – do nothing
        return;                          // goto switchD_… which returns immediately
    }                                    // Fall through for states 0x0A-0x19

    // ------------------------------------------------------------------------
    // States 0x0A ... 0x19 (in-game sub-menus)
    // ------------------------------------------------------------------------
    pComponent = (int*)getScreenManager();           // FUN_00ad8d40 – returns global screen manager
    if (pComponent == nullptr)
        return;

    // Get the active UI script component from the screen manager (vcall at +0x48)
    pComponent = (int*)(**(code**)(*pComponent + 0x48))();

    // Determine which text array to use based on active input device
    isActive = isControllerActive();                 // FUN_00917010
    if (isActive != 0 && gControllerTextEnabled != 0)   // DAT_00e54cd8
    {
        pTextArray = *(undefined4**)(gControllerTextArray + *extraOutEDX * 4); // DAT_00e54cd4
    }
    else
    {
        isActive = isKeyboardActive();               // FUN_00917030
        if (isActive != 0 && gKeyboardTextEnabled != 0) // DAT_00e54cf0
        {
            pTextArray = *(undefined4**)(gKeyboardTextArray2 + *extraOutEDX * 4); // DAT_00e54cec
        }
        else
        {
            // States 0x12-0x18 are handled with a special text array
            if (state >= 0x12 && state <= 0x18 && gSpecialTextEnabled != 0) // DAT_00e54cfc
            {
                pTextArray = *(undefined4**)(gSpecialTextArray + *extraOutEDX * 4); // DAT_00e54cf8
                goto useText;
            }
            // State 0x19 uses yet another array
            if (state == 0x19)
            {
                if (gState19TextEnabled == 0)        // DAT_00e54ce4
                    return;
                pTextArray = *(undefined4**)(gState19TextArray + *extraOutEDX * 4); // DAT_00e54ce0
            }
            else
            {
                return;
            }
        }
    }

useText:
    textStr = (char*)*pTextArray;
    if (textStr == nullptr)
        textStr = (char*)&defaultMenuItemText;    // DAT_0120546e

    // Clear a buffer (maybe input or display list)
    clearDisplayBuffer(&gMenuBuffer, 0);            // FUN_00402050

    // Build a list of menu items from this screen
    buildMenuItemList(this, &gMenuListFormat, 0);   // FUN_009192b0

    // Call virtual function on the UI component to set the active text
    (**(code**)(*pComponent + 0x40))(&textStr, 1, &stackVar); // vcall +0x40

    return;
}