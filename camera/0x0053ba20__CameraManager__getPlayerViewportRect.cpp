// FUNC_NAME: CameraManager::getPlayerViewportRect

struct ViewportRect {
    int32_t left;    // +0x00
    int32_t top;     // +0x04
    int32_t right;   // +0x08
    int32_t bottom;  // +0x0C
};

// Globals
extern int32_t g_currentPlayerIndex;          // DAT_01125388
extern uint8_t* g_playerDataArray;             // DAT_01125414 (array of 0x38-byte entries)
extern void* g_gameManagerInstance;            // DAT_011252e8
extern int32_t g_defaultViewportSize;          // DAT_00e2b1a4

// Forward declaration – retrieves actual viewport from player-specific data
void getPlayerViewportFromData(void* manager, void* playerData, ViewportRect* outRect); // FUN_0060add0

void CameraManager::getPlayerViewportRect(ViewportRect& outRect) {
    outRect.left   = 0;
    outRect.top    = 0;
    outRect.right  = g_defaultViewportSize;
    outRect.bottom = g_defaultViewportSize;

    // Calculate offset into per-player data array (0x38 bytes per player)
    int32_t offset = g_currentPlayerIndex * 0x38;
    int32_t* playerDataPtr = (int32_t*)(g_playerDataArray + offset);

    if (*playerDataPtr != 0) {
        // Player data exists – fill real viewport rectangle
        getPlayerViewportFromData(g_gameManagerInstance, (void*)*playerDataPtr, &outRect);
    }
    // else: use default full‑screen rectangle
}