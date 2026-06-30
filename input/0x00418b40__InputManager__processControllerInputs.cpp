// FUNC_NAME: InputManager::processControllerInputs
void __thiscall InputManager::processControllerInputs(uint32_t this_ptr, uint32_t controllerConfig, uint32_t arg3, uint32_t arg4)
{
    uint32_t systemData;
    uint32_t configField;
    uint32_t frameState;
    char debugFlag;

    // Retrieve pointer to global system state from thread-local storage (FS:[0x2C])
    systemData = *(uint32_t*)(*(uint32_t*)(__readfsdword(0x2C))); // +0x00

    // First input value: from system buffer at offset 0x70 + config field (+0x18)
    uint32_t inputValue = *(uint32_t*)(*(uint32_t*)(systemData + 8) + 0x70 + *(uint32_t*)(controllerConfig + 0x18));

    // Debug check (global flag at 0x011f7430)
    debugFlag = FUN_004166b0();
    if (debugFlag != 0 && (*(uint32_t*)0x011f7430 & 1) != 0) {
        FUN_00614a50(); // Log debug output
    }

    // Update internal frame timing
    FUN_00490d70();

    // Get per-player input state (stored at this+4)
    frameState = *(uint32_t*)(this_ptr + 4);

    // Store first input value at offset 0x1B4
    *(uint32_t*)(frameState + 0x1B4) = inputValue;

    // Second input value: read from config's field (+0x18) as base, plus 0x78 plus system data (+8)
    *(uint32_t*)(frameState + 0xF0) = *(uint32_t*)(*(uint32_t*)(controllerConfig + 0x18) + 0x78 + *(uint32_t*)(systemData + 8));

    // Continue processing (deadzone, smoothing, etc.)
    FUN_00418540(controllerConfig, arg3, arg4);
}