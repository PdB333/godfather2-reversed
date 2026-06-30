// FUNC_NAME: UIHudMinimapMarkerManager::getMarkerScreenPosition
// Address: 0x005ec6d0
// This function computes the screen position of a minimap marker and returns
// packed coordinates with a success flag. It checks if the minimap is visible
// and if the marker container is valid. Access to screen coordinate system
// via stack-based push/pop helpers.

#include <cstdint>

// Forward declarations of internal helpers (likely EA engine functions)
extern bool __stdcall isMinimapVisible();  // FUN_005e9d10
extern void __cdecl beginScreenCoordinateAccess();  // FUN_00c9eac0
extern void __cdecl getScreenCoordinate(int id, double *out); // FUN_00c9cd20 (id 1=?, id 2=?)
extern void __cdecl endScreenCoordinateAccess(); // FUN_00c9eae0

// Global scale factor (e.g., UI scale)
extern float g_uiScale; // DAT_00e44570

// Class: UIHudMinimapMarkerManager (size unknown, but contains:
// +0x580: int* pMarkerTarget (some pointer checked for non-null)
// +0x5b0: MarkerEntry[MAX_MARKERS] (size 0xF8 per entry)
// MarkerEntry at +0x00: uint32_t markerData (texture ID or unique identifier)
struct UIHudMinimapMarkerManager;

// Method: getMarkerScreenPosition
// Parameters:
//   markerIndex: index into the marker array (max 0x7F)
//   outMarkerData: receives the marker's data (e.g., texture handle) from the array
//   outScreenX: receives computed screen X coordinate (scaled)
//   outScreenY: receives computed screen Y coordinate (scaled)
// Returns: packed int where low byte = 1 if success, upper 24 bits = (Y_orig * scale) >> 8
int __thiscall UIHudMinimapMarkerManager::getMarkerScreenPosition(
    unsigned short markerIndex,
    uint32_t *outMarkerData,
    int *outScreenX,
    int *outScreenY)
{
    // Default outputs
    *outMarkerData = 0;
    *outScreenX = 0;
    *outScreenY = 0;

    // Check if minimap subsystem is active and we have a valid marker target
    if (markerIndex < 0x80)
    {
        if (!isMinimapVisible())
        {
            // Return failure (low byte not set)
            return 0;
        }
        // Check if the marker pointer at +0x580 is non-null
        if (*(int *)(this + 0x580) != 0)
        {
            double coordA = 0.0; // local_10
            double coordB = 0.0; // local_18

            // Push current screen coordinate transform
            beginScreenCoordinateAccess();

            // Retrieve two coordinates (likely min/max or base offsets)
            getScreenCoordinate(1, &coordA); // e.g., left/top edge
            getScreenCoordinate(2, &coordB); // e.g., right/bottom edge

            // Pop transform
            endScreenCoordinateAccess();

            // Compute screen X as (coordB - coordA) * global scale
            *outScreenX = static_cast<int>((coordB - coordA) * g_uiScale);
            // Compute screen Y as coordA * global scale
            *outScreenY = static_cast<int>(coordA * g_uiScale);

            // Fetch the marker's data from the array at +0x5b0 (each entry 0xF8 bytes)
            // index * 0xF8 + offset + this
            *outMarkerData = *(uint32_t *)((uintptr_t)markerIndex * 0xF8 + this + 0x5b0);

            // Build return value: low byte = 1 (success), high 24 bits = (Y_orig * scale) >> 8
            // Note: The original uses local_10 (coordA) directly, so Y_orig = coordA * scale
            uint32_t yShifted = (static_cast<uint32_t>(*outScreenY) >> 8) & 0x00FFFFFF;
            return (yShifted << 8) | 0x00000001;
        }
        // Fall through: if pointer at +0x580 is null, do nothing
    }

    // Return failure
    return 0;
}