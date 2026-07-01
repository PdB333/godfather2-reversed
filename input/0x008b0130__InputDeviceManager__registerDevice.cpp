// FUNC_NAME: InputDeviceManager::registerDevice
void __thiscall InputDeviceManager::registerDevice(InputDeviceManager* this, InputDevice* device)
{
    // Store device pointer at offset +0x40
    this->m_device = device;

    // Call virtual function at vtable offset 0xac (43rd entry) on the device
    // This is likely a device initialization or start method
    device->vtable->method43();

    // Copy a timestamp from a global singleton (DAT_01129908 + 0x14) to offset +0x3c
    // This might be the time when the device was registered
    this->m_registrationTime = *(uint32_t*)((uint8_t*)g_TimeManager + 0x14);
}