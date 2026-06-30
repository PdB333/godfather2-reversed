// FUNC_NAME: ObjectManager::findObjectByQuadHandle
// Address: 0x006bca80
// This function searches a global list of objects for one whose 4-int handle (at offsets 0x20, 0x24, 0x28, 0x2c) matches the given key.
// Returns a pointer to the object if found, or nullptr.

#include <cstdint>

// Global array of object pointers
extern void** s_objectHandleList; // DAT_0112a6a0
// Global count of objects in the list
extern uint32_t s_objectHandleCount; // DAT_0112a6a4

struct QuadHandle {
    int32_t a; // offset 0x00 relative to handle
    int32_t b; // offset 0x04
    int32_t c; // offset 0x08
    int32_t d; // offset 0x0C
};

void* findObjectByQuadHandle(const QuadHandle* handle) {
    if (s_objectHandleCount == 0) {
        return nullptr;
    }
    for (uint32_t i = 0; i < s_objectHandleCount; i++) {
        void* obj = s_objectHandleList[i];
        if (handle->a == *(int32_t*)((uint8_t*)obj + 0x20) &&
            handle->b == *(int32_t*)((uint8_t*)obj + 0x24) &&
            handle->c == *(int32_t*)((uint8_t*)obj + 0x28) &&
            handle->d == *(int32_t*)((uint8_t*)obj + 0x2c)) {
            return obj;
        }
    }
    return nullptr;
}