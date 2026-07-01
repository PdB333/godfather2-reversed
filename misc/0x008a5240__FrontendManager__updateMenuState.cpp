// FUNC_NAME: FrontendManager::updateMenuState
void FrontendManager::updateMenuState(int* param1, int* param2)
{
    bool isFrontendActive;
    int menuOptionCount;
    int selectedOptionIndex;
    int nextMenuState;
    char* playerObj; // DAT_01129930
    int* gameManager;
    int* frontendManager;
    int* menuManager;
    int frontendScriptState;
    int currentState;
    bool isPlayerDon;
    bool isJoinerStrictNAT;

    // Step 1: Get the game manager and the frontend/menu manager chain
    gameManager = (int*)GameManager::getInstance(); // FUN_00ad8d40
    if (gameManager != nullptr)
    {
        frontendManager = (int*)(*(code**)(*gameManager + 0x34))(); // getFrontendManager
        if (frontendManager != nullptr)
        {
            menuManager = (int*)(*(code**)(*frontendManager + 0x3c))(); // getMenuManager
        }
    }

    // Step 2: Check if we are in the FrontendMainLoop state
    currentState = *(int*)(DAT_0112b9b4 + 0x40); // globals
    int scriptHandle = ScriptManager::findScript("FrontendMainLoop"); // FUN_00683280
    frontendScriptState = ScriptManager::getScriptState(scriptHandle); // FUN_006833d0

    // Compare with global state (DAT_0112980c + 4)
    if ((frontendScriptState == *(int*)(DAT_0112980c + 4)) &&
        (DAT_01129930 != 0) &&
        (*(char*)(DAT_01129930 + 0x48) != '\0') &&
        ((*(byte*)(DAT_01129930 + 0x49) & 0x0A) == 0))
    {
        isFrontendActive = true;
    }
    else
    {
        isFrontendActive = false;
        // If frontend not active, early exit with special states
        if (currentState == 0)
        {
            nextMenuState = 2; // Possibly "go to main menu"
            goto callSetResult;
        }
        if (*(int*)(currentState + 0xd8) > 2)
        {
            nextMenuState = 3; // "go to exit"
            goto callSetResult;
        }
    }

    // Step 3: Get current menu option count and selected index from menuManager
    menuOptionCount = (**(code**)(*menuManager + 0x18))(); // getOptionCount
    selectedOptionIndex = (**(code**)(*menuManager + 0x60))(); // getSelectedIndex

    int diff = (menuOptionCount - selectedOptionIndex) + 1;
    if (diff < 1)
    {
        goto callSetResult;
    }

    // Step 4: Check various conditions based on player state and network
    playerObj = (char*)DAT_01129930; // Global player object
    isPlayerDon = (**(code**)(*param2 + 0x28))("IsPlayerDon", 0); // Check if player is Don

    // Use local_8 as a temporary int (stack variable)
    int* tempStruct = &local_8; // Actually we need to allocate, but decompiler shows local_8 as int on stack

    // The condition for bVar1 (isFrontendActive) and playerObj valid
    if (isFrontendActive && (playerObj != nullptr) && (*(char*)(playerObj + 500) != '\0'))
    {
        if (!isPlayerDon)
        {
            // Non-Don player: if diff == 1 and option displayed == 1, set special state
            if ((diff == 1) && (*(int*)(playerObj + 0x1e4) == 1))
            {
                nextMenuState = (menuOptionCount - selectedOptionIndex) + 0x3f;
                goto callSetResult;
            }
        }
        else
        {
            // Don player: if option displayed == 4, set state 0x3e
            if (*(int*)(playerObj + 0x1e4) == 4)
            {
                nextMenuState = 0x3e;
                goto callSetResult;
            }
        }

        // If player is Don and above didn't trigger, set option displayed to 4 and call helper
        if (isPlayerDon)
        {
            *(int*)(playerObj + 0x1e4) = 4;
            MenuHelper::func_008a3be0(playerObj + 0x1a8); // FUN_008a3be0
        }
    }

    // Step 5: Handle NAT joiner strictness
    int* tempFlag = &local_8; // Actually local_8 is a temporary flag variable
    *tempFlag = 1; // local_c = 1
    nextMenuState = 0;

    isJoinerStrictNAT = (**(code**)(*param2 + 0x28))("JoinerStrictNAT", 0);
    // If JoinerStrictNAT is not set, or function check fails, we proceed
    if ((!isJoinerStrictNAT) || (FUN_008a4f60() != '\0'))
    {
        // param2 is used as a buffer? Possibly a network config structure.
        if (*(int*)(local_8 + 8) != 0) // checks some condition on tempStruct
        {
            FUN_008a4510(&local_8, &param2); // Setup something
            *(uint*)(local_8 + 4) = (uint)(isJoinerStrictNAT != 0) * 2; // set flags
        }
    }
    else
    {
        *tempFlag = 0; // local_c = 0
        nextMenuState = 0x3d; // Direct to "strict NAT" state
    }

callSetResult:
    // Final call to set the result on the menu manager
    (**(code**)(*menuManager + 0x34))(param1, *tempFlag, nextMenuState);
    return;
}