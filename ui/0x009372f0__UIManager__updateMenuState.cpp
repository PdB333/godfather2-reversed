// FUNC_NAME: UIManager::updateMenuState
void __fastcall UIManager::updateMenuState(int thisPtr)
{
    int *stateObjectPtr;
    // Stack structure for cleanup call
    struct {
        int data1;      // +0x00
        int data2;      // +0x04
        char data3;     // +0x08
    } cleanupArgs;

    switch (*(int *)(thisPtr + 0x50)) // current menu state
    {
    case 0: // State 0
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank"); // reset movie frame
        g_uiMovieState1[0x16] = 0; // +0x16: sub-state field
        stateObjectPtr = g_uiMovieState1;
        break;
    case 1: // State 1
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank");
        g_uiMovieState1[0x16] = 1;
        stateObjectPtr = g_uiMovieState1;
        break;
    case 2: // State 2
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank");
        g_uiMovieState2[0x16] = 0;
        stateObjectPtr = g_uiMovieState2;
        break;
    case 3: // State 3
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank");
        g_uiMovieState2[0x16] = 1;
        stateObjectPtr = g_uiMovieState2;
        break;
    case 4: // State 4
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank");
        g_uiMovieState2[0x16] = 2;
        stateObjectPtr = g_uiMovieState2;
        break;
    case 5: // State 5
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank");
        g_uiMovieState2[0x16] = 3;
        stateObjectPtr = g_uiMovieState2;
        break;
    case 6: // State 6
        flashCall("gotoAndStop", 0, &DAT_00d8a0dc, 1, "fr_blank");
        g_uiMovieState2[0x16] = 4;
        stateObjectPtr = g_uiMovieState2;
        break;
    default:
        goto defaultHandler;
        // unreachable
    }
    // Call virtual function at vtable index 10 on the selected state object
    (*(void (**)(void))(*stateObjectPtr + 0x28))();
    return;

defaultHandler:
    cleanupArgs.data1 = DAT_01130448;
    cleanupArgs.data2 = 0;
    cleanupArgs.data3 = 0;
    cleanup(&cleanupArgs, 0);
    return;
}