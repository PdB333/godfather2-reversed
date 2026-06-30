// FUNC_NAME: registerControllerDevice

#include <cstdint>

// Global variables from the binary
extern uint32_t g_currentSlotIndex;       // DAT_01219b21 - index into controller slot array
extern void* g_registeredDevice;          // _DAT_01219b30 - the device pointer passed in EAX

// Each controller slot is 0x3C bytes
struct ControllerSlot {
    void* device;      // +0x00
    uint8_t pad0C[0xC]; // padding to offset +0x0C
    void* state;       // +0x0C
    // remaining bytes to reach 0x3C
};

extern ControllerSlot g_controllerSlots[]; // base at DAT_01219d44

// Forward declaration of the function called when device and state are both present
void initializeControllerDevice();

// Registers a device (pointer in EAX) and possibly triggers initialization
void registerControllerDevice() {
    void* device;
    
    // The device pointer is passed in EAX (hardware register convention in this build)
    // In standard C++ this would be a parameter; here we assume it's read from EAX
    // and stored in assembly. For reconstruction we treat it as input.
    g_registeredDevice = device;
    
    // Check if the current slot has both device and state pointers non-null
    if (g_controllerSlots[g_currentSlotIndex].device != 0 &&
        g_controllerSlots[g_currentSlotIndex].state != 0) {
        initializeControllerDevice();
    }
}