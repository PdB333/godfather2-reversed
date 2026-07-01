// FUNC_NAME: UIHudMinimapMarkerManager::updateMarkerPosition
// Address: 0x00958e00
// Sets marker screen coordinates from world coordinates relative to a rectangle.
// Used for minimap icon positioning.

void __thiscall UIHudMinimapMarkerManager::updateMarkerPosition(void *this, int markerId, float minX, float minY, float maxX, float maxY)
{
    float worldX, worldY;
    float scaleX; // from global DAT_00d5eee4
    float offsetX; // from global _DAT_00d5780c
    void *hudManager; // from DAT_01129a74

    // Mark this marker as visible/active
    *(uint8_t *)((uint8_t *)this + 0x2ad) = 1;

    hudManager = DAT_01129a74; // global pointer to HUD manager instance

    // Set the world-to-screen mapping rectangle (min/max) - used for other markers?
    FUN_00926890(1, minX, minY, maxX, maxY); // 1 might indicate minimap or specific layer

    // Clear a "dirty" or "recalculate" flag on the HUD manager
    *(uint8_t *)((uint8_t *)hudManager + 0x3a3) = 0;

    // Get the world position of the referenced object (e.g., player or target)
    FUN_00926810(&worldX, &worldY); // typically returns player position

    // Constants for minimap scaling (likely screenWidth/Height related)
    scaleX = DAT_00d5eee4;   // +0x0: probably half of minimap width in screen coords
    offsetX = _DAT_00d5780c; // +0x0: probably center offset (e.g., 0.5f)

    // Compute normalized screen X within the minimap rectangle
    *(float *)((uint8_t *)this + 0x2b8) = ((worldX - minX) * scaleX) / (maxX - minX) - offsetX;

    // Same for Y (uses same constants)
    *(float *)((uint8_t *)this + 0x2bc) = ((worldY - minY) * scaleX) / (maxY - minY) - offsetX;

    // Store marker ID
    *(int *)((uint8_t *)this + 0x2b4) = markerId;

    return;
}