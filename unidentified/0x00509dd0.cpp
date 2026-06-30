// FUN_00509dd0: DeviceManager::createDevice

#include <cstdint>

// Global variables
extern int32_t gDeviceCount;          // DAT_010c2250
extern ControllerDevice* gDeviceInstance;   // DAT_0112509c
extern void* PTR_PTR_011250a0;        // vtable for ControllerDevice (or derived)

// Helper function declarations (guessed from usage)
int32_t FUN_00513df0(__out int32_t& outParam1, __out int32_t& outParam2); // Returns something
void* operator new(size_t size);     // FUN_009c8e50
ControllerDevice* ControllerDeviceConstructor(int32_t param1, int32_t param2); // FUN_00513bc0

// Factory function
ControllerDevice* DeviceManager::createDevice()
{
    ControllerDevice* device = nullptr;

    // Check if we have enough device "slots" (gDeviceCount is a divisor of 0x2a0)
    if (gDeviceCount / 0x2a0 > 0)
    {
        int32_t context1, context2;
        FUN_00513df0(&context1, &context2);

        void* mem = operator new(0x24); // sizeof(ControllerDevice) = 0x24
        if (mem == nullptr)
        {
            device = nullptr;
        }
        else
        {
            device = ControllerDeviceConstructor(context1, context2);
        }
        gDeviceInstance = device;
        if (device != nullptr)
        {
            // Set vtable pointer at offset 0x20 (multiple inheritance or custom vtable offset)
            *(void***)((uint8_t*)device + 0x20) = &PTR_PTR_011250a0;
        }
    }
    return device;
}