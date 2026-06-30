// FUNC_NAME: bringWindowToForeground
void bringWindowToForeground(HWND hWnd)
{
    BOOL success = SetForegroundWindow(hWnd);
    if (success)
    {
        ShowWindow(hWnd, SW_SHOWNORMAL); // SW_SHOWNORMAL = 1
    }
    return;
}