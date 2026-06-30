// FUNC_NAME: Application::WndProc
LRESULT CALLBACK Application::WndProc(HWND hWnd, uint uMsg, uint wParam, uint lParam)
{
    char handledFlag[4];  // passed to PreMsgHandler, first byte indicates if message was handled
    LRESULT handledResult;
    tagRECT clientRect;
    ushort uVar2;
    ushort uVar3;
    int iVar4;
    BOOL bRet;
    uint uVar8;

    // Global state variables
    // DAT_0112a024 = g_hMainWnd
    // DAT_0112a028 = g_bActive
    // DAT_0112a02a = g_bUnknownFlag
    // DAT_0112a02c = g_iSizeState (0=normal,1=minimized? 2=maximized?)
    // DAT_0112a030 = g_iClientWidth
    // DAT_0112a034 = g_iClientHeight
    // DAT_0112a038 = g_restoreLeft
    // DAT_0112a03c = g_restoreTop
    // DAT_0112a040 = g_hSomeObject (returned from InitWindow)
    // DAT_0112a044 = g_bAutoRepeatEnabled
    // DAT_0112a048 = g_bFullscreen

    // Special case: WM_ACTIVATEAPP with window handle mismatch triggers OnActivateApp
    if (uMsg == 0x1c && hWnd == DAT_0112a024 && DAT_0112a02a != '\0' &&
        ((wParam != 0) != (bool)DAT_0112a028) && wParam == 0) {
        FUN_0069ddc0();  // likely handle deactivation
    }

    // Pre-handler: may handle message and return early
    FUN_0069eb50(handledFlag, hWnd, uMsg, wParam, lParam, DAT_0112a024, DAT_0112a028);
    if (handledFlag[0] != '\0') {
        return handledResult;
    }

    // Extract HIWORD of lParam for size messages
    ushort hiWordLParam = (ushort)(lParam >> 16);

    if (uMsg < 0x101) {
        if (uMsg == 0x100) { // WM_KEYDOWN
            if (DAT_0112a044 != 0) {
                for (uVar8 = lParam & 0xffff; uVar8 != 0; uVar8--) {
                    FUN_0098d450();  // handle key repeat
                }
            }
            goto DefWindow;
        }

        switch (uMsg) {
        case 1: // WM_CREATE
            bRet = GetClientRect(hWnd, &clientRect);
            if (bRet != 0) {
                DAT_0112a030 = (short)clientRect.right;
                DAT_0112a034 = (short)clientRect.bottom;
            }
            DAT_0112a024 = hWnd;
            _DAT_0112a040 = FUN_0069d680(hWnd, DAT_00d5cf54, DAT_00d5cf5c); // init
            break;

        case 2: // WM_DESTROY
            FUN_0069d6e0(); // cleanup
            PostQuitMessage(0);
            return 0;

        case 3: // WM_MOVE (0x0003)
            if (hWnd == DAT_0112a024) {
                IsIconic(DAT_0112a024);
            }
            return 0;

        case 5: // WM_SIZE
            if (hWnd == DAT_0112a024) {
                if (wParam == 1) {
                    DAT_0112a02c = 2; // maximized
                } else if (wParam == 2) {
                    DAT_0112a02c = 1; // minimized
                } else if (DAT_0112a02c != 0) {
                    DAT_0112a02c = 0; // restored
                }
                DAT_0112a030 = (short)lParam;
                DAT_0112a034 = hiWordLParam;
                char cVar1 = FUN_0060e860(); // check fullscreen/active
                if (cVar1 == '\0') {
                    GetWindowLongA(hWnd, -0x10); // GWL_WNDPROC
                    FUN_0060e870();
                }
                FUN_0069dd70(); // handle size
            }
            return 0;

        case 0xf: // WM_PAINT
            {
                char cVar = FUN_0060e860();
                if ((cVar == '\0') && (bRet = IsWindowVisible(hWnd), bRet == 0)) {
                    return 1; // blocked if not active and not visible
                }
                ValidateRect(hWnd, NULL);
            }
            return 0;

        case 0x10: // WM_CLOSE
            {
                char cVar = FUN_0069db60(); // ask if game wants to close
                if (cVar != '\0') {
                    FUN_0069d620(); // perform close
                }
            }
            return 0;

        case 0x14: // WM_ERASEBKGND
            return 1; // suppress erase

        case 0x1c: // WM_ACTIVATEAPP
            if ((hWnd == DAT_0112a024) && (DAT_0112a02a == '\0') &&
                ((wParam != 0) != (bool)DAT_0112a028)) {
                DAT_0112a028 = wParam != 0; // update active state
                char cVar = FUN_0060e860();
                if ((cVar != '\0') && (DAT_0112a028 == '\0')) {
                    ShowWindow(hWnd, 6); // SW_MINIMIZE
                    cVar = FUN_0060e860();
                    if ((cVar == '\0') && (DAT_0112a048 == '\0')) {
                        DAT_0112a048 = FUN_0069dce0(); // toggle fullscreen
                    }
                    SetActiveWindow(NULL);
                }
                FUN_0069d3f0(); // handle activation change
            }
            break;

        case 0x7e: // WM_DISPLAYCHANGE
            {
                char cVar = FUN_0060e860();
                if ((cVar != '\0') && (bRet = IsIconic(DAT_0112a024), bRet != 0)) {
                    DAT_0112a038 = (short)lParam;
                    DAT_0112a03c = hiWordLParam;
                }
            }
            break;

        case 0x84: // WM_NCHITTEST
            {
                char cVar = FUN_0060e860();
                if (cVar != '\0') {
                    return 1; // always hit client area in fullscreen
                }
            }
            // fall through to DefWindowProc
        }
    } else {
        if (uMsg < 0x213) {
            if (uMsg == 0x212) { // WM_MOUSELEAVE
                FUN_0069d240(); // handle mouse leave
            } else if (uMsg < 0x106) {
                if (uMsg == 0x105) { // WM_SYSKEYUP
                    return 0;
                }
                if (uMsg == 0x102) { // WM_CHAR
                    if (DAT_0112a044 != 0) {
                        for (uVar8 = lParam & 0xffff; uVar8 != 0; uVar8--) {
                            FUN_0098aaf0(); // handle character repeat
                        }
                    }
                } else if (uMsg == 0x104) { // WM_SYSKEYDOWN
                    if (wParam != 0x73) { // if not F10
                        return 0;
                    }
                    if ((lParam >> 0x1d & 1) == 0) { // check context code
                        return 0;
                    }
                    // F10 with Alt down triggers close
                    goto closeLabel;
                }
            } else if (uMsg == 0x112) { // WM_SYSCOMMAND
                {
                    char cVar = FUN_0060e860();
                    if (cVar != '\0') {
                        uVar8 = wParam & 0xfff0;
                        if (uVar8 == 0xf000 || uVar8 == 0xf010 || uVar8 == 0xf030) {
                            return 0; // ignore SC_SIZE, SC_MOVE, SC_MAXIMIZE
                        }
                    }
                    if (wParam == 0xf060) { // SC_CLOSE? Actually 0xF060 is SC_WAITICON? Let's keep original.
                        uVar2 = GetAsyncKeyState(0x73); // F10
                        uVar3 = GetAsyncKeyState(0x12); // Alt
                        if ((short)(uVar2 & uVar3) < 0) {
                            return 0; // block Alt+F10
                        }
                    } else {
                        if (wParam == 0xf100) { // SC_SCREENSAVE
                            return 0;
                        }
                        if (wParam == 0xf140) { // SC_TASKLIST
                            return 0;
                        }
                    }
                }
            } else if (uMsg == 0x211) { // detailed? Actually 0x211 is WM_MOVE? But WM_MOVE is 0x0003. Could be WM_ENTERSIZEMOVE? 0x231/0x232? Not sure.
                FUN_0069d240(); // same as mouse leave? Might be WM_ENTERSIZEMOVE?
            }
            goto DefWindow;
        }

        switch (uMsg) {
        case 0x218: // unknown, maybe WM_DESTROYCLIPBOARD? Actually 0x218 is WM_UNKNOWN.
            if (wParam == 0) {
                return 0x424d5144; // "BMQD" signature? Possibly for splash screen.
            }
            break;

        case 0x219: // WM_POWERBROADCAST? Actually 0x219 is WM_POWERBROADCAST? No, 0x218/0x219 are unusual.
            if ((wParam == 0x8004) && (DAT_0112a028 != '\0')) {
                iVar4 = FID_conflict_operator__(&DAT_00d5cf54); // likely comparison
                if (iVar4 != 0) {
                    FUN_0040fa00(); // handle power event
                }
            }
            goto displayChangeLabel;

        case 0x231: // WM_CLIPBOARDUPDATE
            FUN_0069d670();
            break;

        case 0x232: // WM_CHANGECBCHAIN
            if (hWnd == DAT_0112a024) {
                FUN_0069ddc0();
            }
            return 0;
        }
    }

    // label for close case
closeLabel:
    {
        char cVar = FUN_0069db60();
        if (cVar != '\0') {
            FUN_0069d620();
        }
        return 0;
    }

    // label for display change case
displayChangeLabel:
    {
        char cVar = FUN_0060e860();
        if ((cVar != '\0') && (bRet = IsIconic(DAT_0112a024), bRet != 0)) {
            DAT_0112a038 = (short)lParam;
            DAT_0112a03c = hiWordLParam;
        }
        goto DefWindow;
    }

DefWindow:
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}