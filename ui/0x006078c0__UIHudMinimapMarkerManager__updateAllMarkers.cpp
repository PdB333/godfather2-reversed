// FUNC_NAME: UIHudMinimapMarkerManager::updateAllMarkers
void __cdecl UIHudMinimapMarkerManager::updateAllMarkers() {
    bool useWorldProjection;
    char checkResult;
    float finalX, finalY;
    float* pMarkerData;
    int markerIndex;

    // gCurrentGameState = DAT_00f15a1c (0x15 = free roam / no mission?)
    if (gCurrentGameState == 0x15) {
        checkResult = FUN_0060f540(); // likely checks if game is not paused
        useWorldProjection = false;
        if (checkResult == '\0') goto SKIP_UPDATE;
    }
    useWorldProjection = true;
SKIP_UPDATE:
    markerIndex = 0;
    if (0 < gMarkerCount) {
        // gMarkerArray = DAT_01205778 (array of MarkerData, stride 0x18)
        pMarkerData = (float*)&gMarkerArray;
        do {
            if (useWorldProjection) {
                MarkerData* marker = (MarkerData*)(pMarkerData - 4); // adjust pointer to get struct start
                // If isWorldCoord flag is 0, use pre-set screen coordinates
                if (marker->isWorldCoord == '\0') {
                    finalY = marker->screenY;   // +4
                } else {
                    finalY = (float)(int)(gScreenScaleY * marker->worldY); // +16
                    if ((int)finalY < 1) {
                        finalY = 0.0f; // FLT_EPSILON? Actually 1.4013e-45 is min positive float
                    }
                }
                if (marker->isWorldCoord == '\0') {
                    finalX = marker->screenX;   // +0
                } else {
                    finalX = (float)(int)(gScreenScaleX * marker->worldX); // +12
                    if ((int)finalX < 1) {
                        finalX = 0.0f;
                    }
                }
            } else {
                finalY = 0.0f;
                finalX = 0.0f;
            }
            // Call virtual method at vtable+0x70 on gRenderer
            // (DAT_01205750 is a renderer object, likely a sprite renderer)
            (**(void (__thiscall**)(void*, float, float, int, int, int, int, void*, int))(*gRenderer + 0x70))
                (gRenderer, finalX, finalY, gCurrentGameState, 0, 0, 0, pMarkerData + 1, 0);
            // pMarkerData+1 points to extra data (string/icon index) at offset 0x14 from struct start
            markerIndex++;
            pMarkerData += 6; // advance by 6 floats (24 bytes)
        } while (markerIndex < gMarkerCount);
    }
}