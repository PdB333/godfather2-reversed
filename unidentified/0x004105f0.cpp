// FUN_004105f0: InputManager::initializeControllerSlot
void __thiscall InputManager::initializeControllerSlot(int slotIndex)
{
    // +0x6a: array of ControllerSlot structures (0x44 bytes each)
    // +0x4ec: array of device object pointers (4 bytes each, indexed by slot)
    // +0x544: input buffer / event sink pointer
    // +0x564: keyboard device slot index
    // +0x565: DirectInput device slot index

    // Probably enters some critical section or takes a lock
    GlobalLock();

    int deviceType = GetDeviceTypeForSlot(slotIndex); // 0 = none, 1 = XInput, 2 = keyboard, 3 = DirectInput

    if (deviceType == 0) {
        // No device plugged in – clear the slot state
        *(byte*)(this + 0x6A + slotIndex * 0x44) = 0;
        return;
    }

    int typeId = *(int*)(deviceType + 4); // Some type identifier? Possibly from a device description struct.
    // typeId ranges: 0/1 = XInput, 2 = Keyboard, 3 = DirectInput

    if (typeId == 0 || typeId == 1) {
        // XInput device
        void* mem = AllocateMemory(0x120); // size of XInputDevice object
        void* device = mem ? ConstructXInputDevice() : nullptr;

        *(void**)(this + 0x4EC + slotIndex * 4) = device;

        if (device && !IsXInputAvailable()) {
            // XInput not available – destroy device and clear slot
            if (device) {
                // Call virtual Release(1)
                (*(void (__thiscall**)(void*, int))(*(int*)device))(device, 1);
            }
            *(void**)(this + 0x4EC + slotIndex * 4) = nullptr;
            *(byte*)(this + 0x6A + slotIndex * 0x44) = 0;
            return;
        }

        // Compare device name with "XInput Device" – the name is retrieved into local buffer
        char deviceName[36];
        // Assume deviceName is filled by a call to GetDeviceName(device) that Ghidra omitted
        InitializeDeviceName(device, deviceName);

        bool nameMatch = true;
        const char* xinputStr = "XInput Device";
        for (int i = 0; i < 14; i++) {
            if (deviceName[i] != xinputStr[i]) {
                nameMatch = false;
                break;
            }
        }
        // Call some function that finalizes initialization, possibly associating device with name
        FinalizeDeviceInitialization(deviceName, deviceType, nameMatch);
        return;
    }

    if (typeId == 3) {
        // DirectInput device
        void* mem = AllocateMemory(0x1C0);
        void* device = mem ? ConstructDirectInputDevice(slotIndex) : nullptr;
        device = DirectInputDeviceSetup(device);
        *(void**)(this + 0x4EC + slotIndex * 4) = device;
        *(byte*)(this + 0x565) = (byte)slotIndex; // Store the DirectInput slot index
        return;
    }

    if (typeId == 2) {
        // Keyboard device
        void* mem = AllocateMemory(0x130);
        int* device = mem ? (int*)ConstructKeyboardDevice() : nullptr;
        *(int**)(this + 0x4EC + slotIndex * 4) = device;
        *(byte*)(this + 0x564) = (byte)slotIndex; // Store the keyboard slot index
        if (device) {
            // +300 field: likely pointer to input sink / buffer
            *(int*)(device + 300) = (int)(this + 0x544);
        }
        return;
    }
}