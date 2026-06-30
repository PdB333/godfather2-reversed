// FUNC_NAME: SetGlobal16IntBlock
// Function address: 0x00612310
// Stores 16 integers into global array at 0x011f6690 and optionally notifies a listener via function pointer.

#include <cstdint>

// Global array at 0x011f6690 (16 DWORDs)
static uint32_t g_globalData[16];

// Global pointer at 0x012058e8 to a management object with:
// +0x10: object pointer for listener (uint32_t)
// +0x5c: function pointer for notification (uint32_t)
extern uint32_t g_pListenerManager;

// Function pointer type for the notification callback (__thiscall on listenerObject)
typedef void (__thiscall *ListenerCallback)(uint32_t thisObj, uint32_t* data);

// Forward declaration of the called function (FUN_0060b020)
void CallListenerFunction(uint32_t listenerObject, uint32_t functionPtr, uint32_t* data);

void SetGlobal16IntBlock(uint32_t* data) {
    // Copy first 16 integers into the global array
    g_globalData[0] = data[0];
    g_globalData[1] = data[1];
    g_globalData[2] = data[2];
    g_globalData[3] = data[3];
    g_globalData[4] = data[4];
    g_globalData[5] = data[5];
    g_globalData[6] = data[6];
    g_globalData[7] = data[7];
    g_globalData[8] = data[8];
    g_globalData[9] = data[9];
    g_globalData[10] = data[10];
    g_globalData[11] = data[11];
    g_globalData[12] = data[12];
    g_globalData[13] = data[13];
    g_globalData[14] = data[14];
    g_globalData[15] = data[15];

    // Notify listener if manager and callback are valid
    if (g_pListenerManager != 0) {
        uint32_t listenerObject = *(uint32_t*)(g_pListenerManager + 0x10);
        uint32_t listenerFunc   = *(uint32_t*)(g_pListenerManager + 0x5c);
        if (listenerFunc != 0) {
            CallListenerFunction(listenerObject, listenerFunc, data);
        }
    }
}

// External function implementation (at 0x0060b020)
void CallListenerFunction(uint32_t listenerObject, uint32_t functionPtr, uint32_t* data) {
    // Reinterpret the function pointer and call with __thiscall convention
    ListenerCallback callback = reinterpret_cast<ListenerCallback>(functionPtr);
    callback(listenerObject, data);
}