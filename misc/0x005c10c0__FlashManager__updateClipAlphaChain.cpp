// FUNC_NAME: FlashManager::updateClipAlphaChain

// Function at 0x005c10c0
// Iterates backwards over an array of display objects (indexed by g_currentObjectIndex),
// retrieves a clip identifier from each, and sets the alpha of the corresponding _root.<id>.<id>._alpha
// movie clip to either 100 (visible) or 0 (hidden) based on a flag returned by getClipInfo().

#include <cstdio>

// Global state
static int g_currentObjectIndex;               // DAT_00f17914: current index into object array
static void* g_objectArray[/*some size*/];     // DAT_01205608: array of object pointers
static char g_pathBuffer[5];                   // DAT_01223564: 4-character clip ID buffer + null terminator

// Forward declarations of called functions
// Returns a 64-bit value: low 32 bits = pointer to clip object, high 32 bits = visibility flag
extern uint64_t getClipInfo(void* gameObject);

// Sets the alpha value of a Scaleform movie clip given its path
extern void setMovieAlpha(const char* path, int alpha);

// Virtual method at index 1 on the clip object's vtable (at offset 0x10)
// Returns a 32-bit value encoding a 4-character clip name
typedef uint32_t (__thiscall* GetClipIdFn)(void* clipObject);

void FlashManager::updateClipAlphaChain() {
    // Check if current index is valid and the object at that index exists
    if (g_currentObjectIndex < 0) return;
    void* currentObject = g_objectArray[g_currentObjectIndex];
    if (currentObject == 0) return;

    // Retrieve clip info (pointer + flag)
    uint64_t clipInfo = getClipInfo(currentObject);
    void* clipObject = (void*)(uint32_t)clipInfo;       // low 32 bits
    bool bVisible = (clipInfo >> 32) != 0;              // high 32 bits

    if (clipObject != 0) {
        do {
            // Call virtual method at offset 0x10, entry 1 (GetClipId)
            GetClipIdFn getClipId = *(GetClipIdFn*)(*(uint32_t*)((uint8_t*)clipObject + 0x10) + 4);
            uint32_t clipId = getClipId(clipObject);

            // Store clip ID as 4 characters (big-endian order)
            g_pathBuffer[0] = (char)(clipId >> 24);
            g_pathBuffer[1] = (char)(clipId >> 16);
            g_pathBuffer[2] = (char)(clipId >> 8);
            g_pathBuffer[3] = (char)(clipId);
            g_pathBuffer[4] = 0;  // null terminator

            // Build movie path: "_root.<id>.<id>._alpha"
            char moviePath[256];
            sprintf(moviePath, "_root.%s.%s._alpha", g_pathBuffer, g_pathBuffer);

            // Set alpha to 100 if visible, 0 if hidden
            int alpha = bVisible ? 100 : 0;
            setMovieAlpha(moviePath, alpha);

            // Move backward in the object array to find the previous non-zero entry
            int searchIndex = g_currentObjectIndex;
            if (searchIndex < 0) return;
            do {
                if (g_objectArray[searchIndex] == currentObject) break;
                searchIndex--;
            } while (searchIndex >= 0);
            searchIndex--;  // skip the current object
            if (searchIndex < 0) return;

            // Skip zero entries
            while (g_objectArray[searchIndex] == 0) {
                searchIndex--;
                if (searchIndex < 0) return;
            }

            currentObject = g_objectArray[searchIndex];
            if (currentObject != 0) {
                clipInfo = getClipInfo(currentObject);
                clipObject = (void*)(uint32_t)clipInfo;
                bVisible = (clipInfo >> 32) != 0;
            }
        } while (clipObject != 0);
    }
}