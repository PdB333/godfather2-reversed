// FUNC_NAME: CameraManager::updateActiveViewport
// Address: 0x00535640
// Sets up an active viewport entry in the viewport pool, returns its index,
// and fills output arrays with projection ratio and viewport rectangle.

#include <cstdint>

// Forward declarations
struct ViewportEntry; // 0x38 bytes per entry
struct ViewportSystem; // Global system pointer

// Globals extracted from the binary
extern ViewportSystem* g_viewportSystem;          // DAT_012054dc
extern uint32_t g_defaultViewportIndex;           // DAT_012058a8
extern float g_projectionScale;                   // DAT_00e2b1a4
extern ViewportEntry g_viewportPool[];            // DAT_011a0f28
extern uint32_t g_viewportX;                      // DAT_011f6a98
extern uint32_t g_viewportY;                      // DAT_011f6aa8
extern uint32_t g_viewportWidth;                  // DAT_011f6a9c
extern uint32_t g_viewportHeight;                 // DAT_011f6aac

// External functions
extern void memoryRelease(void* ptr, uint32_t tag); // FUN_00606e60
extern void viewportStateChanged();                 // FUN_006189c0

// ViewportEntry layout (0x38 bytes)
struct ViewportEntry {
    uint8_t state;              // +0x00: state, compared to 4
    uint8_t pad1[0x0B];         // padding
    uint32_t flags;             // +0x0C: flags modified with 0x210000
    // ... other fields ...
    void* somePointer;          // +0x1C: pointer released with memoryRelease
};

// ViewportSystem: holds active viewport index at offset 0x170
struct ViewportSystem {
    uint8_t pad0[0x170];
    uint32_t activeViewportIndex; // +0x170
};

uint32_t __cdecl CameraManager::updateActiveViewport(
    float nearPlane,          // XMM input (in_XMM0_Da)
    float farPlane,           // XMM input (in_XMM1_Da)
    float* outProjectionInfo, // param_1: array of at least 2 floats
    uint32_t* outViewportRect // param_2: array of 4 uints (x, y, w, h)
)
{
    uint32_t viewportIndex = g_defaultViewportIndex;

    if (g_viewportSystem != nullptr) {
        // Use the system's active viewport index
        viewportIndex = g_viewportSystem->activeViewportIndex;
    }

    // Validate index (must be present and within reasonable range)
    if ((viewportIndex != 0xFFFFFFFF) && (viewportIndex < 0x1000)) {
        ViewportEntry* entry = &g_viewportPool[viewportIndex];

        // If entry is active (state < 4) and has an attached pointer, release it
        if ((entry->state < 4) && (entry->somePointer != nullptr)) {
            memoryRelease(entry->somePointer, 0x210000);
        }

        // Update flags: clear certain bits and set 0x210000
        entry->flags = (entry->flags & 0xFCAD8FFF) | 0x210000;

        // Notify system that viewport state changed
        viewportStateChanged();
    }

    // Output projection information
    // outProjectionInfo[0] = g_projectionScale / (farPlane - nearPlane)  // depth scaling factor
    // outProjectionInfo[1] = nearPlane
    *outProjectionInfo = g_projectionScale / (farPlane - nearPlane);
    outProjectionInfo[1] = nearPlane;

    // Output viewport rectangle (from global configuration)
    outViewportRect[0] = g_viewportX;
    outViewportRect[1] = g_viewportY;
    outViewportRect[2] = g_viewportWidth;
    outViewportRect[3] = g_viewportHeight;

    return viewportIndex;
}