// FUNC_NAME: RenderDebug::updateOverlayVisibility

// Reconstructed C++ for function at 0x007e1700
// This function toggles rendering of debug overlays based on various game state checks.
// It appears to be part of the debug rendering system (likely from EARS::Modules::Debug or similar).
// Offsets documented: this+0x58 -> pointer to overlay data structure (mOverlayData)
// OverlayData+0x8e0 bit 4 -> flag for "overlay enabled"
// OverlayData+0xe80 -> some render flag/toggle

#include <cstdint>

// Forward declarations of external functions (addresses known)
bool IsGameActive();                              // 0x00481640
void* GetRenderInterface();                       // 0x007ab170
void* GetSomeObject();                            // 0x007ff880 (returns pointer to something with +0xe80)
void SetRenderTarget(uint32_t target);            // 0x0043b870 (likely sets a render target)
bool IsOverlayActive();                           // 0x009a9460
bool IsOverlayVisible(void* someObject);          // 0x009a9750

// The class that owns this method
class RenderDebug {
public:
    void updateOverlayVisibility() __fastcall;
    // Members inferred:
    // +0x58: mOverlayData (pointer to overlay-specific data)
    // ...
};

// Implementation
void __fastcall RenderDebug::updateOverlayVisibility() {
    // Fetch pointer to overlay data from this object
    int* overlayData = *(int**)(this + 0x58);  // +0x58: mOverlayData

    // Check if game is active (not paused, in menu, etc.)
    if (IsGameActive()) {
        // Game is active – skip overlay updates
        return;
    }

    // Get the render interface singleton (likely DebugRenderer or similar)
    int* renderInterface = (int*)GetRenderInterface();
    // Enable two base render flags (possibly for overlay drawing)
    (*(void(__stdcall*)(uint32_t))*renderInterface)(0x10000000);
    (*(void(__stdcall*)(uint32_t))*renderInterface)(0x20000000);

    // Check if the overlay data has a "enabled" flag (bit 4 of field at +0x8e0)
    if (((*(uint32_t*)(overlayData + 0x8e0) >> 4) & 1) != 0) {
        int* someObject = (int*)GetSomeObject();  // returns something like a camera or entity
        if (someObject != nullptr) {
            // Read a flag from that object's field +0xe80
            int renderFlag = *(int*)(someObject + 0xe80);

            // Set a specific render target (maybe a texture for the overlay)
            SetRenderTarget(0x01130fa0);  // global texture/resource

            // Check if the overlay system is active globally
            if (IsOverlayActive()) {
                // Re-fetch someObject (doesn't change result but needed for visibility check)
                void* someObjAgain = GetSomeObject();
                if (IsOverlayVisible(someObjAgain)) {
                    // Toggle the overlay render flag between 0x10000000 and 0x20000000
                    // depending on whether renderFlag is nonzero
                    // Computes: if renderFlag != 0 then 0x20000000 else 0x10000000
                    uint32_t toggleFlag = ((-(uint32_t)(renderFlag != 0) & 0x10000000) + 0x10000000);
                    (*(void(__stdcall*)(uint32_t))(renderInterface + 4))(toggleFlag);
                }
            }
        }
    }
}