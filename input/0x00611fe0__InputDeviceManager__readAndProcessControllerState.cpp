// FUNC_NAME: InputDeviceManager::readAndProcessControllerState
// Function at 0x00611fe0: Copies raw controller state from two sources into global arrays, then processes sub-objects for vibration/effects update.
// This function is called from two places (0x00614910, 0x00614ab0) and likely runs each frame.
// Global pointers are used (gInputDeviceManager at 0x012058e8).
// Two source pointers (ESI, EDI) point to 64-byte controller state structures (e.g. XINPUT_STATE).

#include <cstdint>

// Global arrays storing controller state (16 dwords each)
static uint32_t gController1State[16]; // at 0x011f6640
static uint32_t gController2State[16]; // at 0x011f6720

// Global pointer to InputDeviceManager singleton
static void* gInputDeviceManager; // at 0x012058e8

// Forward declarations of sub-functions (addresses 0x0060b020 and 0x0060aea0)
// These take a primary sub-object pointer and a secondary sub-object pointer.
extern void deviceManagerUpdateSub1(void* primaryObj, void* secondaryObj);
extern void deviceManagerUpdateSub2(void* primaryObj, void* secondaryObj);

void InputDeviceManager::readAndProcessControllerState(uint32_t* src1, uint32_t* src2)
{
    // Copy 16 dwords from each source into global state buffers
    for (int i = 0; i < 16; ++i) {
        gController1State[i] = src1[i];
        gController2State[i] = src2[i];
    }

    // Process the InputDeviceManager singleton if it exists
    if (gInputDeviceManager != nullptr) {
        // Pointer-sized data at various offsets inside the manager object.
        // Offsets:
        // +0x10: primary sub-object A (e.g., left controller handler)
        // +0x14: primary sub-object B (e.g., right controller handler)
        // +0x30: secondary sub-object A1
        // +0x34: secondary sub-object A2
        // +0x38: secondary sub-object A3
        // +0x7c: secondary sub-object B1
        // +0x80: secondary sub-object B2
        // +0x84: secondary sub-object B3

        void* primaryA = *(void**)((uint8_t*)gInputDeviceManager + 0x10);
        void* primaryB = *(void**)((uint8_t*)gInputDeviceManager + 0x14);

        // Check and call update functions for each sub-object if non-null
        void* subA1 = *(void**)((uint8_t*)gInputDeviceManager + 0x30);
        if (subA1 != nullptr) {
            deviceManagerUpdateSub1(primaryA, subA1);
        }

        void* subB1 = *(void**)((uint8_t*)gInputDeviceManager + 0x7c);
        if (subB1 != nullptr) {
            deviceManagerUpdateSub1(primaryB, subB1);
        }

        void* subA2 = *(void**)((uint8_t*)gInputDeviceManager + 0x34);
        if (subA2 != nullptr) {
            deviceManagerUpdateSub2(primaryA, subA2);
        }

        void* subB2 = *(void**)((uint8_t*)gInputDeviceManager + 0x80);
        if (subB2 != nullptr) {
            deviceManagerUpdateSub2(primaryB, subB2);
        }

        void* subA3 = *(void**)((uint8_t*)gInputDeviceManager + 0x38);
        if (subA3 != nullptr) {
            deviceManagerUpdateSub2(primaryA, subA3);
        }

        void* subB3 = *(void**)((uint8_t*)gInputDeviceManager + 0x84);
        if (subB3 != nullptr) {
            deviceManagerUpdateSub2(primaryB, subB3);
        }
    }
}