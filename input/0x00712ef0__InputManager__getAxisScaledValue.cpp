// FUNC_NAME: InputManager::getAxisScaledValue
float InputManager::getAxisScaledValue(int axisIndex) {
    // Global default sensitivity scale (e.g., master sensitivity setting)
    float scale = g_defaultInputScale; // _DAT_00d5780c

    // Pointer to per-controller settings at offset +0x10 from this InputManager
    ControllerSettings* settings = *(ControllerSettings**)((uint8_t*)this + 0x10);
    // Check bit 10 in a flags field at offset +0x8e0 of the settings object
    // Indicates if a custom sensitivity profile is active for this controller
    if (settings && (*(uint32_t*)((uint8_t*)settings + 0x8e0) >> 10 & 1) != 0) {
        // Retrieve the active controller profile (singleton)
        ControllerProfile* profile = getActiveControllerProfile(); // FUN_00800a90
        if (profile != nullptr) {
            // Custom sensitivity scale stored at +0x338 of the profile
            scale = *(float*)((uint8_t*)profile + 0x338);
        }
    }

    // Read raw axis value from the array at this+0x4c, indexed by axisIndex
    float rawAxis = *(float*)((uint8_t*)this + 0x4c + axisIndex * 4);
    return rawAxis * scale;
}