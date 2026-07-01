// FUNC_NAME: Application::handleWindowEvent
void Application::handleWindowEvent(int param_1, int param_2, char param_3)
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;
    
    if (param_2 != 0) {
        // Process window message
        FUN_009823b0();
        FUN_009c8eb0(param_2);
    }
    if ((param_3 == '\0') && (param_1 != -1)) {
        // Window closed or destroyed, quit application
        PostQuitMessage(0);
        return;
    }
    // Default window procedure handling
    local_c = DAT_011303e8;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    return;
}