// FUNC_NAME: InputDeviceManager::getActiveDevicePriority
// Address: 0x00949080
// Role: Determines the priority of active input devices by checking two device hashes.
// Returns 2 if first device (hash 0x55859efa) is present, 1 if second (hash 0x6f1d0554) is present, else 0.
// The virtual function at vtable+0x10 (isDevicePresent) takes a hash and an output pointer (unused here).

int InputDeviceManager::getActiveDevicePriority() {
    int outParam = 0;
    if (this != nullptr) {
        // Check highest priority device (e.g., keyboard)
        if (this->isDevicePresent(0x55859efa, &outParam)) {
            return 2;
        }
        // Check medium priority device (e.g., gamepad)
        if (this->isDevicePresent(0x6f1d0554, &outParam)) {
            return 1;
        }
    }
    return 0; // No device active
}