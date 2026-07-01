// FUNC_NAME: InputDeviceManager::initDevices
void __thiscall InputDeviceManager::initDevices() {
    // Base initialization (likely sets up default state for input devices)
    FUN_005c1740();

    // Register keyboard device (device type 0) at this+0x58
    FUN_005c01d0(&DAT_00d85730, this + 0x58, 0, 0, 0, 1);

    // Register mouse device (device type 6) at this+0x54
    FUN_005c01d0(&DAT_00d88708, this + 0x54, 6, 0, 0, 1);

    // Register gamepad device (device type 1) at this+0x5c
    FUN_005c01d0(&DAT_00d8d840, this + 0x5c, 1, 0, 0, 1);
}