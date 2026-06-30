// FUNC_NAME: InputDeviceManager::init
void InputDeviceManager::init(void)
{
    // Zero out fields at offsets +0x54, +0x58, +0x60, +0x64, +0x68, +0x6c, +0x70, +0x74
    *(int *)(this + 0x54) = 0;      // unknown uint, likely a counter or flag
    *(int *)(this + 0x58) = 0;      // 
    *(int *)(this + 0x60) = 0;
    *(int *)(this + 100)  = 0;      // decimal 100 = 0x64
    *(int *)(this + 0x68) = 0;
    *(int *)(this + 0x6c) = 0;
    *(int *)(this + 0x70) = 0;
    *(char *)(this + 0x74) = 0;     // byte flag

    // Set field at +0x5c to 0x1000 (4096) - likely a buffer size, max slots, or timeout
    *(int *)(this + 0x5c) = 0x1000;

    // Call internal sub‑initializers
    FUN_00648930();                                        // likely this->initSubroutine()
    FUN_00648b00(DAT_01205410, DAT_01205418);              // init with global configuration data
}