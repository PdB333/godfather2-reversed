// FUNC_NAME: setControllerRumbleState

void setControllerRumbleState(void)
{
    uint i;

    // Check if current controller ID matches an entry in the mapping table
    for (i = 0; i < 20; i++) {
        if (g_controllerMapping[i].controllerId == g_currentControllerId) {
            // If the matching slot is valid (i < 20) and has the "rumble disabled" flag (bit 2) set,
            // call a special rumble function and exit early.
            if ((i < 20) && ((g_controllerMapping[i].flags & 0x02) != 0)) {
                FUN_00609810(); // Likely stop rumble or set a different effect
                return;
            }
            break;
        }
    }

    // First rumble effect block: left motor speed = 0x34 (52)
    if (g_leftMotorSpeed < 0x34) {
        g_leftMotorSpeed = 0x34;
    }
    if (0x34 < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x34;
    }
    g_rumbleEffectType = 1;     // +0x??: rumble effect type (1 = left motor?)
    FUN_0041e4d0(3, 1, 1);     // Set rumble effect: (effectIndex, ?, ?)

    // Second rumble effect block: left motor speed = 0x38 (56)
    if (g_leftMotorSpeed < 0x38) {
        g_leftMotorSpeed = 0x38;
    }
    if (0x38 < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x38;
    }
    g_rumbleEffectDuration = 8; // +0x??: rumble duration in seconds?
    if (g_leftMotorSpeed < 0x39) {
        g_leftMotorSpeed = 0x39;
    }
    if (0x39 < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x39;
    }
    g_rumbleEffectRepeat = 0;   // +0x??: repeat count?
    if (g_leftMotorSpeed < 0x3a) {
        g_leftMotorSpeed = 0x3a;
    }
    if (0x3a < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x3a;
    }
    g_rumbleEffectFlags = 0xFF; // +0x??: flags (0xFF = enable both motors?)

    // Apply these parameters to the rumble system
    FUN_004e2b30(); // Likely apply rumble effect parameters

    // Second pass: switch to a different rumble effect type (1 instead of 3)
    if (g_leftMotorSpeed < 0x34) {
        g_leftMotorSpeed = 0x34;
    }
    if (0x34 < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x34;
    }
    g_rumbleEffectType = 0;
    FUN_0041e4d0(1, 1, 1);     // Set different rumble effect

    if (g_leftMotorSpeed < 0x38) {
        g_leftMotorSpeed = 0x38;
    }
    if (0x38 < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x38;
    }
    g_rumbleEffectDuration = 8;
    if (g_leftMotorSpeed < 0x39) {
        g_leftMotorSpeed = 0x39;
    }
    if (0x39 < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x39;
    }
    g_rumbleEffectRepeat = 0;
    if (g_leftMotorSpeed < 0x3a) {
        g_leftMotorSpeed = 0x3a;
    }
    if (0x3a < g_rightMotorSpeed) {
        g_rightMotorSpeed = 0x3a;
    }
    g_rumbleEffectFlags = 0xFFFFFFFF; // Disable motors? (0xFFFFFFFF = -1, all bits set)
    return;
}