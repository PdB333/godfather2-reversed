// FUNC_NAME: InputManager::applyAnalogDeadZone
// Address: 0x006c9eb0
// Role: Applies dead zone scaling to analog stick input (steering/throttle) for a controller.
// Checks for controller connection, dead zone thresholds, and global flags.
// Outputs normalized values in range [0,1] after removing dead zone.

void __thiscall InputManager::applyAnalogDeadZone(
    int controllerIndex,        // param_2: index of controller to read
    float* outStickX,           // param_3: output for horizontal axis (e.g., steering)
    float* outStickY,           // param_4: output for vertical axis (e.g., throttle)
    float deadZoneX,            // param_5: dead zone threshold for X
    float deadZoneY)            // param_6: dead zone threshold for Y
{
    // Check if controller is disconnected, analog input disabled, or keyboard/mouse active
    if ((*(int*)(this + 0x6c) == -1) ||  // +0x6c: active controller index; -1 means disconnected
        (DAT_00e50fb5 == '\0') ||        // global flag: likely "analog input enabled"
        ((int*)(*(int*)(DAT_012233a0 + 4)) != 0 &&  // global pointer to input device config
         ((*(int*)(*(int*)(DAT_012233a0 + 4) + 0x570) >> 0x14 & 1) != 0)))  // +0x570: flags; bit 20 = keyboard/mouse
    {
        *outStickX = 0.0f;
        *outStickY = 0.0f;
        return;
    }

    // Read raw analog values from controller hardware (left stick by default)
    // FUN_00465e30 takes: controller index (from this+0x6c), axis flags, pointers to outputs, and scale factors
    // Here it reads left/right (param_2 flags?) and stores raw values into outStickX/outStickY
    FUN_00465e30(*(char*)(this + 0x6c), controllerIndex, outStickX, outStickY, 0, 0,
                 DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);

    // Dead zone and scaling constants (likely from global input settings)
    float maxRange = DAT_00e44564;       // maximum analog value (e.g., 32767)
    float minRange = _DAT_00d5780c;      // minimum analog value (range = max - min? Actually used as max? Misnamed)
    // _DAT_00d5780c appears to be the maximum absolute value (e.g., 32767)
    // Dead zone removal: subtract dead zone from raw value, scale to [0,1] based on remaining range

    float rawX = *outStickX;
    if (maxRange - deadZoneX <= rawX) {
        if (rawX <= deadZoneX) {
            *outStickX = 0.0f;
        } else {
            rawX = rawX - deadZoneX;
        }
    } else {
        rawX = rawX + deadZoneX;
    }
    *outStickX = rawX / (minRange - deadZoneX);

    float rawY = *outStickY;
    if (rawY < maxRange - deadZoneY) {
        *outStickY = (rawY + deadZoneY) / (minRange - deadZoneY);
        return;
    }
    if (deadZoneY < rawY) {
        *outStickY = (rawY - deadZoneY) / (minRange - deadZoneY);
        return;
    }
    *outStickY = 0.0f;
}