// FUNC_NAME: CameraManager::updateCameraProjection

#include <cstdint>

// Globals (external defined elsewhere)
extern uint32_t DAT_012058a8;           // default camera slot index
extern uint32_t* DAT_012054dc;          // pointer to game object (e.g. camera manager) with camera index at +0x170
extern uint8_t DAT_011a0f28[];          // array of camera slots, each 0x38 bytes
extern float DAT_00e2b1a4;             // constant for projection scaling (e.g., 1.0f / tan(fov/2))
extern float DAT_011f6a98;             // projection parameter 0 (e.g., near plane distance)
extern float DAT_011f6a9c;             // projection parameter 1 (e.g., far plane distance)
extern float DAT_011f6aa8;             // projection parameter 2 (e.g., left frustum edge)
extern float DAT_011f6aac;             // projection parameter 3 (e.g., right frustum edge)

// Forward declarations of called functions
void FUN_00606e60(int ptr, uint32_t flags);   // likely free/release resource
void FUN_006189c0();                         // unknown, maybe notify state change

// Camera slot structure offsets
// +0x00: uint8_t state (0=inactive, 1=active, 2=...)
// +0x0c: uint32_t flags
// +0x1c: int renderResourcePtr (non-zero indicates allocated resource)

uint32_t CameraManager::updateCameraProjection(float* outParams, uint32_t* outViewport)
{
    // Determine current camera slot index
    uint32_t cameraIndex = DAT_012058a8;
    if (DAT_012054dc != nullptr) {
        cameraIndex = *(uint32_t*)(DAT_012054dc + 0x170); // +0x170: offset to active camera index
    }

    if ((cameraIndex != 0xffffffff) && (cameraIndex < 0x1000)) {
        int slotOffset = cameraIndex * 0x38;
        uint8_t* cameraSlot = &DAT_011a0f28[slotOffset];

        if ((cameraSlot != nullptr) && (cameraSlot[0] < 4)) {
            // Release previous render resource if allocated
            int* resourcePtr = (int*)(&DAT_011a0f44[slotOffset]); // +0x1c within slot
            if (*resourcePtr != 0) {
                FUN_00606e60(*resourcePtr, 0x210000);
            }
            // Update flags: clear bits 0x0327000 (0xfcad8fff mask) and set 0x210000
            uint32_t* flags = (uint32_t*)(&DAT_011a0f34[slotOffset]); // +0x0c
            *flags = (*flags & 0xfcad8fff) | 0x210000;
            FUN_006189c0();
        }
    }

    // Compute projection parameters
    float scaleFactor = DAT_00e2b1a4;      // e.g., 1.0f / tan(fov/2)
    float yDiff = in_XMM1_Da - in_XMM0_Da; // input Y range (top - bottom?)
    
    outParams[0] = scaleFactor / yDiff;     // e.g., 1/(top-bottom) for projection matrix
    outParams[1] = in_XMM0_Da;             // bottom (or near)
    outViewport[0] = *(uint32_t*)&DAT_011f6a98; // left or near
    outViewport[1] = *(uint32_t*)&DAT_011f6aa8; // top or far
    outViewport[2] = *(uint32_t*)&DAT_011f6a9c; // right or aspect
    outViewport[3] = *(uint32_t*)&DAT_011f6aac; // bottom or unknown

    return cameraIndex;
}