// FUNC_NAME: ResolutionManager::getMappedResolution
// Address: 0x00609260
// Role: Looks up a resolution mapping table to return a scaled or raw value based on input width/height.
// Uses global resolution table (0x18 byte entries) and a return value array (6 ints per entry).

#include <cstdint>

// Global flags and data (addresses from Ghidra)
extern bool g_bResolutionEnabled;          // DAT_011f3910
extern int32_t g_DefaultReturnValue;       // DAT_0120577c
extern uint16_t g_ResolutionMode;          // DAT_011f3914
extern int32_t g_ResolutionTableCount;     // DAT_00f15a6c
extern uint8_t g_ResolutionTable[];        // DAT_01205770 (array of ResolutionEntry)
extern float g_ScaleX;                     // DAT_0120587c
extern float g_ScaleY;                     // DAT_01205880
extern int32_t g_ReturnValueArray[];       // DAT_0120577c (actually same as default? but used as array)

// Forward declaration of setup function
void setupResolutionMode(uint16_t mode);   // FUN_006066e0

// Structure for each entry in the resolution table (size 0x18 = 24 bytes)
struct ResolutionEntry {
    uint32_t rawWidth;      // +0x00
    uint32_t rawHeight;     // +0x04
    uint8_t  useScale;      // +0x08 (0 = use raw, non-zero = use scaled)
    float    scaleX;        // +0x0C
    float    scaleY;        // +0x10
    // padding 4 bytes at +0x14? (size 0x18)
};

// Function: getMappedResolution
// Returns a mapped value (int32) for given width/height.
int32_t __cdecl getMappedResolution(uint16_t width, uint16_t height) {
    if (!g_bResolutionEnabled) {
        return g_DefaultReturnValue;
    }

    setupResolutionMode(g_ResolutionMode);

    for (int32_t i = 0; i < g_ResolutionTableCount; i++) {
        ResolutionEntry* entry = reinterpret_cast<ResolutionEntry*>(&g_ResolutionTable[i * sizeof(ResolutionEntry)]);
        uint32_t mappedWidth;
        uint32_t mappedHeight;

        if (entry->useScale == 0) {
            mappedWidth  = entry->rawWidth;
            mappedHeight = entry->rawHeight;
        } else {
            mappedWidth  = static_cast<uint32_t>(g_ScaleX * entry->scaleX);
            mappedHeight = static_cast<uint32_t>(g_ScaleY * entry->scaleY);
            if (mappedWidth < 1)  mappedWidth = 1;
            if (mappedHeight < 1) mappedHeight = 1;
        }

        if (mappedWidth == width && mappedHeight == height) {
            // Return the first int of the 6-int block corresponding to this entry
            return g_ReturnValueArray[i * 6];
        }
    }

    return g_DefaultReturnValue;
}