// FUNC_NAME: Building::updateMaxFloorHeight

#include <cstdint>

// Global data: count and array of floor objects
extern int g_floorCount;          // DAT_01162387
extern void* g_floorArray[];      // DAT_01194ae0

// Helper: retrieves the height of a floor into outHeight
void getFloorHeight(void* floor, float* outHeight); // FUN_0051b5f0

void __thiscall Building::updateMaxFloorHeight() {
    if (g_floorCount != 0) {
        float maxHeight = 0.0f;
        for (int i = 0; i < g_floorCount; i++) {
            float height;
            getFloorHeight(g_floorArray[i], &height);
            if (maxHeight <= height) {
                maxHeight = height;
            }
        }
        // Store the maximum height into two fields (likely bounding box extents)
        *(float*)((uint8_t*)this + 0x8C) = maxHeight; // +0x8C: m_floorMaxHeight?
        *(float*)((uint8_t*)this + 0x90) = maxHeight; // +0x90: m_floorMaxWidth?
    }
}