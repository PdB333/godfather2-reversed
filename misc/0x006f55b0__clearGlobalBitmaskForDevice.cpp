// FUNC_NAME: clearGlobalBitmaskForDevice
void clearGlobalBitmaskForDevice(void* device)
{
    if (device != nullptr)
    {
        // Read a 32-bit mask from the device structure at offset 0x1c.
        uint deviceMask = *(uint*)((char*)device + 0x1c);

        // Clear only the bits within the 0xff000 range (bits 12-19) from the global flag.
        // This is often used to update a global active-device bitfield after a device disconnects.
        g_globalDeviceFlags = g_globalDeviceFlags & ~deviceMask & 0xff000;
    }
}