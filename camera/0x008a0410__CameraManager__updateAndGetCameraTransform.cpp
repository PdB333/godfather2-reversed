// FUNC_NAME: CameraManager::updateAndGetCameraTransform

#include <cstdint>

// Helper functions (not defined here)
extern void releaseCameraResource(int* resourcePtr);
extern void processFrame();
extern void* getCameraManager();
extern void destroyEmbeddedListNode(int* node);
extern void freeMemory(void* ptr);

// Global vtable pointer
extern int* g_cameraManagerVTable; // 0x0112a874

int* __thiscall CameraManager::updateAndGetCameraTransform(int* thisPtr, float* outTransform) {
    // +0x28: linked list of camera objects (each node: +0 next, +4 prev, +8 resource pointer)
    int* node = *(int**)((uint8_t*)thisPtr + 0x28);
    int* listHead = (int*)((uint8_t*)thisPtr + 0x28);

    // Process list: remove dead entries (null resource) or update alive ones
    while (node != listHead) {
        if (node[2] == 0) {
            // Resource is null → remove node from list and free it
            int* nextNode = (int*)node[0];
            int* prevNode = (int*)node[1];
            prevNode[0] = (int)nextNode;
            nextNode[1] = (int)prevNode;
            if (node[2] != 0) {
                releaseCameraResource(&node[2]);
            }
            freeMemory(node);
        } else {
            // Resource alive → update it
            releaseCameraResource(&node[2]);
        }
        node = (int*)node[0]; // move to next
    }

    // Yield 4 frames (likely for internal state to settle)
    for (int i = 0; i < 4; ++i) {
        processFrame();
    }

    // Get singleton manager (first call discarded)
    getCameraManager();
    void* someManager = getCameraManager();

    // Embedded list node at +8 from manager
    int* embeddedNode = *(int**)((uint8_t*)someManager + 8);
    int dummy = 0;
    if (embeddedNode != nullptr) {
        dummy = embeddedNode[1]; // not used
        // Manipulate list to extract node (standard EA list removal)
        *(int**)(embeddedNode + 4) = &embeddedNode; // unlink by pointing prev to itself?
        int* enclosingObject = (int*)((uint8_t*)embeddedNode - 0x48); // offset 0x48 to enclosing object
        destroyEmbeddedListNode(&embeddedNode);

        // Read a field at +0x2494 and call vtable function on global
        uint32_t field2494 = *(uint32_t*)((uint8_t*)enclosingObject + 0x2494);
        (**(void (**)(uint32_t))(*g_cameraManagerVTable + 0x24))(field2494);

        // If enclosing object exists, get camera transform
        if (enclosingObject != nullptr) {
            // +0x54: pointer to a sub-object's vtable (camera data)
            int* cameraDataVtable = (int*)enclosingObject[0x54 / 4];
            // Call second virtual function on that sub-object
            int* cameraData = (int*)((int (__thiscall*)(void))cameraDataVtable[1])();

            // Copy 16 bytes from +0x70 (likely a 4-float transform)
            outTransform[0] = *(float*)((uint8_t*)cameraData + 0x70);
            outTransform[1] = *(float*)((uint8_t*)cameraData + 0x74);
            outTransform[2] = *(float*)((uint8_t*)cameraData + 0x78);
            outTransform[3] = *(float*)((uint8_t*)cameraData + 0x7c);
        }
    }

    return g_cameraManagerVTable; // return global pointer
}