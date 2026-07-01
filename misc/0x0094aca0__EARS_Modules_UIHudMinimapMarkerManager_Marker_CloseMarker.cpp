// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_Marker_CloseMarker
// FUNC_NAME: UIMarker::close
uint __fastcall UIMarker::close(UIMarker *this) {
    uint result = 0;
    // Check if already closing (bit 0 at offset 0x11e)
    if ((*(byte *)((int)this + 0x11e) & 1) == 0) {
        // Start some transaction or begin update
        beginMarkerUpdate();
        // If we have a name string at +0x18 (param_1 + 6 as char*)
        if (*(char *)((int *)this + 6) != '\0') {
            int isVisible = 0;
            char varName[256];
            __snprintf(varName, 0x100, "%s._visible", *(char **)((int *)this + 6));
            getMarkerVariable(varName, &isVisible);
            // If visible AND the 0x11c bit 0x20000 is set (bit 0x11)
            if ((isVisible != 0) && (((uint)this->someFlags >> 0x11 & 1) != 0)) {
                callAction("CloseMarker", 0, (int)&DAT_00d8b2cc, 1, (int)this + 2);
                endMarkerUpdate();
            }
        }
        int *animMgr = (DAT_0112a680 == 0) ? 0 : (DAT_0112a680 + 4);
        registerAnimationCallback(animMgr, &UIMarker_closeAnimCallback1, this->baseField);
        animMgr = (DAT_0112a680 == 0) ? 0 : (DAT_0112a680 + 4);
        registerAnimationCallback(animMgr, &UIMarker_closeAnimCallback2, this->baseField);
        // Clear flag 0x7f (bit 7?) at 0x11c
        this->someFlags &= 0xffffff7f;
        clearMarkerState();
        // Set flag 0x10000 (bit 16) at 0x11c
        this->someFlags |= 0x10000;
        result = 1;
    }
    return result;
}