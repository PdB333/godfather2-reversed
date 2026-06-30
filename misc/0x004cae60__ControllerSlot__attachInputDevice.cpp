// FUNC_NAME: ControllerSlot::attachInputDevice
// Address: 0x004cae60
// Role: Attaches an input device (e.g., XInput controller) to a controller slot.
//        This is part of EA EARS input system with 16 controller slots.
// Structure offsets:
//   +0x04: IInputDevice* device (polymorphic device interface)
//   +0x08: int handle (e.g., XInput device handle, 0 if none)

void ControllerSlot::attachInputDevice(IInputDevice* device, int deviceIndex)
{
    // Store the device interface pointer
    this->device = device;  // +0x04

    // Call virtual method at vtable[2] – likely device->onAttach()
    device->onAttach();

    if (deviceIndex != 0)
    {
        // Acquire platform-specific handle (e.g., XInput handle)
        // FUN_004265d0 – likely acquireXInputHandle(deviceIndex, device)
        this->handle = acquireXInputHandle(deviceIndex, this->device);  // +0x08

        // Call virtual method at vtable[1] – device->setDeviceIndex(deviceIndex, 0)
        device->setDeviceIndex(deviceIndex, 0);

        // Call virtual method at vtable[3] – device->finalizeAttach()
        device->finalizeAttach();
        return;
    }

    // No device index – clear handle and finalize
    this->handle = 0;  // +0x08
    device->finalizeAttach();
}