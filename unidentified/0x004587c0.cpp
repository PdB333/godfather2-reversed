// FUN_004587c0: GamepadManager::setRumbleEffect
void GamepadManager::setRumbleEffect(float param2, float param3, float param4, float param5, float param6)
{
    // Check if gamepad system is initialized
    if (!g_gamepadEnabled)
        return;

    // Begin exclusive access to gamepad hardware (likely a mutex lock)
    g_beginGamepadUpdate();

    // Array of two device pointers at offset +0xA0 from this
    GamepadDevice** deviceArray = reinterpret_cast<GamepadDevice**>(reinterpret_cast<char*>(this) + 0xA0);

    for (int i = 0; i < 2; ++i)
    {
        GamepadDevice* device = deviceArray[i];

        // First set of parameters: associated with the "left" effect motor?
        // Condition checks field at +0x8 (e.g., capability flag)
        if (device->field_0x8 != 0)
        {
            // Clamp param5 (left motor speed) to [0.0, g_maxLeftMotorSpeed]
            float leftSpeed = (param5 > 0.0f) ? ((param5 < g_maxLeftMotorSpeed) ? param5 : g_maxLeftMotorSpeed) : 0.0f;
            g_setEffectParameter(0, leftSpeed); // index 0: motor speed

            // Clamp param4 (motor duration or attack) to [g_minMotorDuration, g_maxMotorDuration]
            float leftDuration = (param4 < g_maxMotorDuration) ? ((param4 > g_minMotorDuration) ? param4 : g_minMotorDuration) : g_maxMotorDuration;
            g_setEffectParameter(1, leftDuration); // index 1: duration/attack

            // Clamp param6 (right motor speed) to [0.0, g_maxRightMotorSpeed]
            float rightSpeed = (param6 > 0.0f) ? ((param6 < g_maxRightMotorSpeed) ? param6 : g_maxRightMotorSpeed) : 0.0f;
            g_setEffectParameter(2, rightSpeed); // index 2: right motor speed
        }

        // Second set of parameters: associated with the "right" effect motor?
        // Condition checks field at +0x4
        if (device->field_0x4 != 0)
        {
            // Clamp param2 (right motor speed) to [0.0, g_maxRightMotorSpeed2]
            float rightSpeed2 = (param2 > 0.0f) ? ((param2 < g_maxRightMotorSpeed2) ? param2 : g_maxRightMotorSpeed2) : 0.0f;
            g_setEffectParameter(0, rightSpeed2); // index 0: motor speed

            // Clamp param3 (motor duration or frequency) to [g_minMotorDuration2, g_maxMotorDuration2]
            float rightDuration = (param3 < g_maxMotorDuration2) ? ((param3 > g_minMotorDuration2) ? param3 : g_minMotorDuration2) : g_maxMotorDuration2;
            g_setEffectParameter(1, rightDuration); // index 1: duration/frequency
        }
    }

    // End exclusive access to gamepad hardware
    g_endGamepadUpdate();
}