// FUNC_NAME: InputManager::setYSensitivity
void __thiscall InputManager::setYSensitivity(int thisPtr, float sensitivity)
{
    float clampedSensitivity;
    float minSensitivity = DAT_00d5ef88; // Minimum Y sensitivity global
    float maxSensitivity = DAT_00d5eee4; // Maximum Y sensitivity global

    // Clamp the input sensitivity to the allowed range
    if (sensitivity <= minSensitivity) {
        clampedSensitivity = minSensitivity;
    } else if (maxSensitivity <= sensitivity) {
        clampedSensitivity = maxSensitivity;
    } else {
        clampedSensitivity = sensitivity;
    }

    // Store the clamped sensitivity in the global variable (likely shared across controllers)
    _DAT_00e50fbc = clampedSensitivity;

    // Store in the instance's member variable at offset 0x24 (Y sensitivity)
    *(float *)(thisPtr + 0x24) = clampedSensitivity;

    // Persist the setting via the configuration system with key "Controls.YSensitivity"
    FUN_0069c010("Controls.YSensitivity", clampedSensitivity);
}