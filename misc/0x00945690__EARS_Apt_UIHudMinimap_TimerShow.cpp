// Xbox PDB: EARS_Apt_UIHudMinimap_TimerShow
// FUNC_NAME: MinimapTimer::showTimer
void __thiscall MinimapTimer::showTimer(int thisPtr, int isPolice, float duration) {
    char timerPath[256];
    char visibilityVar[256];
    char* frameLabel;
    
    frameLabel = PTR_s_bribe_00e567f8; // "bribe"
    if (isPolice != 0) {
        frameLabel = PTR_s_police_00e567fc; // "police"
    }
    
    FUN_00944d60(duration); // probably sets timer duration
    
    // Build the target path for the Flash timline
    if ((PTR_DAT_00e567d4 == (undefined *)0x0) || (*PTR_DAT_00e567d4 == '\0')) {
        _strncpy(timerPath, "mmap/minimap_timer", 0x100);
    } else {
        __snprintf(timerPath, 0x100, "mmap/minimap_timer/%s", PTR_DAT_00e567d4);
    }
    
    // Go to the appropriate frame (bribe or police)
    FUN_005a04a0("gotoAndStop", 0, timerPath, 1, frameLabel);
    
    // Show the timer if not already visible
    if ((*(byte *)(thisPtr + 0xfc) & 1) == 0) {
        __snprintf(visibilityVar, 0x100, "mmap/minimap_timer.%s", "_visible");
        FUN_0059ee00(visibilityVar, 1); // set visibility to true
        *(ushort *)(thisPtr + 0xfc) = *(ushort *)(thisPtr + 0xfc) | 1; // mark as visible
    }
}