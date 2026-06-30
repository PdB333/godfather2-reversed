// FUNC_NAME: UIHudMinimapMarkerManager::renderHudMarkers
void __cdecl UIHudMinimapMarkerManager::renderHudMarkers(uint markerIndex)
{
    // Global arrays (see data refs):
    // s_playerIndex = DAT_01125389, player slot index (0-based, size 0x3c per player)
    // s_playerMarkerTexture[playerIndex] = pointer to a texture/sprite for first layer (+0x00 from base)
    // s_playerMarkerTexture2[playerIndex] = pointer to a second layer texture (at +0x30 from base? base is DAT_011254a0)
    // s_hudMarkerData = array of MarkerData (stride 0x38) at DAT_011a0f28
    //   MarkerData layout: +0x00: unknown, +0x02: screenX (ushort), +0x04: screenY (ushort), ... (56 bytes total)
    // g_hudRenderer = DAT_011252ec, pointer to rendering context/device

    int playerIndex = (uint)DAT_01125389;  // Player index (0-3 typically)
    int* playerTexture = (int*)(&DAT_011254a4 + playerIndex * 0x3c); // First layer texture pointer
    int* playerTexture2 = (int*)(&DAT_011254a0 + playerIndex * 0x3c); // Second layer texture pointer

    // First layer: draw a marker from the data array (if texture exists)
    if (*playerTexture != 0) {
        // Get marker data struct (if index valid)
        if (markerIndex < 0x1000) {
            byte* markerData = &DAT_011a0f28 + markerIndex * 0x38;
            float markerX = (float)(*(ushort*)(markerData + 2));
            float markerY = (float)(*(ushort*)(markerData + 4));
            // Draw the marker at (markerX, markerY) using the texture
            FUN_0060ac80(DAT_011252ec, *playerTexture, &markerX);
        }
    }

    // Second layer: if texture exists, call a reset/clear function (e.g., remove all markers of that type)
    if (*playerTexture2 != 0) {
        FUN_006063b0();
    }
}