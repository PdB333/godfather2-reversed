// FUN_NAME: Global::setCurrentFocus
void __fastcall setCurrentFocus(int newHandle) {
    // g_forceUpdate (0x011272a4) forces update even if same handle
    // g_currentHandle (0x01127300) stores the current handle value
    // g_objectArray (0x011272b4) is an array of pointers (0xC stride) indexed by g_index (0x01127310)
    if (g_forceUpdate != 0 || g_currentHandle != newHandle) {
        g_currentHandle = newHandle;
        // If the object at the current index exists, call update function
        if (*(int *)(&g_objectArray + g_index * 0xC) != 0) {
            FUN_006063b0(); // likely processes the object
        }
    }
}