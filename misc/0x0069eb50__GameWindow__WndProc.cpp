// FUNC_NAME: GameWindow::WndProc

undefined1* GameWindow::WndProc(undefined1* resultStruct, HWND hWnd, uint uMsg, WPARAM wParam, LPARAM lParam, HWND hWndTrack, undefined4 extraParam, char someFlag)
{
  bool bActive;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bHandle;
  undefined8 uVar7;
  tagTRACKMOUSEEVENT trackEvent;

  // Initialize result structure: first byte = 0 (not handled), next 4 bytes = -1 (default result)
  *resultStruct = 0;
  *(undefined4*)(resultStruct + 4) = 0xffffffff;

  // Early exit if the tracked window handle does not match the message window
  if (hWnd != hWndTrack) {
    return resultStruct;
  }

  // Process messages below 0x201
  if (uMsg < 0x201) {
    // WM_MOUSEMOVE (0x200)
    if (uMsg == 0x200) {
      // First mouse move event: request mouse leave tracking and possibly update cursor
      if (g_bMouseTracking == '\0') {
        g_bMouseTracking = '\x01';
        trackEvent.cbSize = 0x10;
        trackEvent.dwHoverTime = 0;
        trackEvent.hwndTrack = hWndTrack;
        trackEvent.dwFlags = 2; // TME_LEAVE
        TrackMouseEvent(&trackEvent);
        // If mouse button is down, check if cursor is in client area and update
        if (g_bMouseButtonDown != '\0') {
          if (g_bMouseInClientArea == '\0') {
            return resultStruct;
          }
          GameWindow::updateMouse();
        }
      }

      // If cursor is in client area, compute delta from previous position
      if (g_bMouseInClientArea != '\0') {
        iVar5 = (int)(short)((uint)lParam >> 0x10); // y from lParam
        uVar7 = GameWindow::computeDelta((int)(short)lParam, iVar5); // returns dx, dy packed
        iVar3 = (int)((ulonglong)uVar7 >> 0x20); // dy
        iVar4 = (int)(short)lParam + (int)uVar7; // new x
        iVar5 = iVar5 + iVar3; // new y
        // Accumulate delta from last position
        g_accDeltaX = g_accDeltaX + ((iVar4 - (int)uVar7) - g_lastMouseX);
        g_accDeltaY = g_accDeltaY + ((iVar5 - iVar3) - g_lastMouseY);
        g_lastMouseX = iVar4;
        g_lastMouseY = iVar5;
        // Set result: handled = 1, result = 0
        *(undefined4*)(resultStruct + 4) = 0;
        *resultStruct = 1;
        return resultStruct;
      }
    }
    else {
      // Other messages below 0x201
      switch(uMsg) {
      case 5: // WM_SIZE
        if (wParam == 0) { // SIZE_RESTORED
          if ((g_bMouseInClientArea != '\0') || (cVar2 = GameWindow::isForeground(), cVar2 != '\0')) {
            GameWindow::updateCursor(extraParam);
            return resultStruct;
          }
        }
        else {
          if (wParam == 1) { // SIZE_MINIMIZED
            goto LAB_0069eeb6;
          }
          if (wParam == 2) { // SIZE_MAXIMIZED
            goto LAB_0069ebdd;
          }
          if ((g_bMouseInClientArea != '\0') || (cVar2 = GameWindow::isForeground(), cVar2 != '\0')) {
            GameWindow::updateCursor(extraParam);
            return resultStruct;
          }
        }
        break;
      case 0x1c: // WM_ACTIVATEAPP
        if (someFlag == '\0') {
          bHandle = wParam != 0;
          bActive = true;
          // Check if we should handle activation normally
          if (((bHandle) && (g_bAlwaysActive != '\0')) && (g_lastActivate != -2) && (g_lastActivate != 1)) {
            bActive = false;
          }
          if (bHandle != (bool)(char)extraParam) {
            if (bHandle) {
              if (bActive) {
                GameWindow::onActivateApp(bHandle);
              }
            }
            else {
              GameWindow::updateCursor(0);
            }
            g_savedCursorHandle = 0;
            g_lastActivate = -2; // 0xfffffffe
            return resultStruct;
          }
        }
        break;
      case 0x47: // WM_WINDOWPOSCHANGED
        if (g_bMouseInClientArea != '\0') {
          GameWindow::updateCursor(extraParam);
          GameWindow::updateCursorRect();
          return resultStruct;
        }
        break;
      case 0x7e: // WM_DISPLAYCHANGE
        if (g_bMouseInClientArea != '\0') {
LAB_0069ebdd:
          GameWindow::updateCursor(extraParam);
          return resultStruct;
        }
        break;
      case 0x84: // WM_NCCALCSIZE
        cVar2 = GameWindow::isForeground();
        if (cVar2 != '\0') {
          *resultStruct = 1;
          *(undefined4*)(resultStruct + 4) = 1;
          g_lastActivate = 1;
          return resultStruct;
        }
        g_lastActivate = DefWindowProcW(hWnd, uMsg, wParam, lParam);
        *(int*)(resultStruct + 4) = g_lastActivate;
        *resultStruct = 1;
        return resultStruct;
      case 0xa0: // WM_NCMOUSEMOVE
        if (g_bNCMouseTracking == '\0') {
          g_bNCMouseTracking = 1;
          trackEvent.cbSize = 0x10;
          trackEvent.dwHoverTime = 0;
          trackEvent.hwndTrack = hWndTrack;
          trackEvent.dwFlags = 0x12; // TME_NONCLIENT | TME_LEAVE
          TrackMouseEvent(&trackEvent);
          return resultStruct;
        }
      }
    }
  }
  else {
    // Messages >= 0x201
    switch(uMsg) {
    case 0x202: // WM_LBUTTONUP
    case 0x205: // WM_RBUTTONUP
    case 0x208: // WM_MBUTTONUP
      if (g_bMouseInClientArea == '\0') {
        GameWindow::updateCursor(extraParam);
        return resultStruct;
      }
      break;
    case 0x211: // WM_ENTERMENULOOP
      g_savedCursorHandle = g_bMouseInClientArea;
LAB_0069eeb6:
      GameWindow::updateCursor(0);
      return resultStruct;
    case 0x212: // WM_EXITMENULOOP
      GameWindow::updateCursor(g_savedCursorHandle);
      break;
    case 0x2a2: // WM_NCMOUSELEAVE
      g_savedCursorHandle = 0;
      g_bNCMouseTracking = 0;
      g_lastActivate = -2;
      return resultStruct;
    case 0x2a3: // WM_MOUSELEAVE
      g_savedCursorHandle = 0;
      g_bMouseTracking = 0;
      g_lastActivate = -2;
      return resultStruct;
    }
  }
  return resultStruct;
}