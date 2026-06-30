// FUNC_NAME: UIHudMinimapMarkerManager::updateMarkerPosition
// Function address: 0x00534ef0
// Role: Updates the screen position of a HUD minimap marker from a data table.
// The marker index is passed via the ESI register (unaff_ESI). Reads 2D coordinates
// (ushort X, Y at offsets +2 and +4) from a global data array with stride 0x38,
// then calls FUN_0060ac80 to set the element's position. Also optionally triggers
// an additional update (FUN_006063b0) for another element type.

// Global data pointers
extern int* g_uiElementTable;       // DAT_01219d48 - Array of structures (stride 0x3C) containing UI element ptrs
extern int* g_uiElementTable2;      // DAT_01219d44 - Similar array for a second element type
extern uint8 g_currentElementIndex; // DAT_01219b21 - Index into the above tables (byte)
extern void* g_uiManager;           // DAT_01219a84 - Some UI manager object

// Data table of marker positions (0x38 bytes per entry, ushort at +2 and +4)
extern uint8 g_markerDataTable[0x1000 * 0x38]; // DAT_011a0f28

// Forward declarations of called functions (assumed signatures)
void __cdecl setMarkerPosition(void* uiManager, void* elementPtr, float* position); // FUN_0060ac80
void __cdecl playMarkerEffect(); // FUN_006063b0

void UIHudMinimapMarkerManager::updateMarkerPosition()
{
    uint8* dataRow;
    float position[2];
    void* elementPtr;

    // Check if the current element (index * 0x3C) has a valid pointer
    elementPtr = *(void**)((uint8*)g_uiElementTable + (uint)g_currentElementIndex * 0x3C);
    if (elementPtr != (void*)0x0) {
        // Use ESI as the marker index (passed by caller)
        if (unaff_ESI < 0x1000) {
            dataRow = &g_markerDataTable + unaff_ESI * 0x38;
        } else {
            dataRow = (uint8*)0x0;
        }
        // Read X coordinate (ushort at offset +2)
        position[0] = (float)*(uint16*)(dataRow + 2);
        if (unaff_ESI < 0x1000) {
            dataRow = &g_markerDataTable + unaff_ESI * 0x38;
        } else {
            dataRow = (uint8*)0x0;
        }
        // Read Y coordinate (ushort at offset +4)
        position[1] = (float)*(uint16*)(dataRow + 4);

        // Update the element's position
        setMarkerPosition(g_uiManager, elementPtr, position);
    }

    // Check second element table
    elementPtr = *(void**)((uint8*)g_uiElementTable2 + (uint)g_currentElementIndex * 0x3C);
    if (elementPtr != (void*)0x0) {
        playMarkerEffect();
    }
    return;
}