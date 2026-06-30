/*
 * Function address: 0x0040faf0
 * Role: Set rumble/vibration value for a controller slot in the XInput-based input system.
 * The input manager has 16 controller slots, each of size 0x44 bytes.
 * Within each slot:
 *   - Offset 0x40: uint16_t rumble value (motor speed)
 *   - Offset 0x6a: char active flag (non-zero if controller is connected/active)
 * The function only writes the rumble value if the controller is active.
 */

void __thiscall ControllerManager::SetControllerRumble(
    int this,
    byte controllerIndex,
    uint16_t rumbleValue)
{
    uint index = (uint)controllerIndex;
    if (index < 0x10) {
        // Check if the controller slot is active (flag at offset 0x6a from slot base)
        if (*(char *)(this + 0x6a + index * 0x44) != '\0') {
            // Write rumble value to offset 0x40 from slot base
            *(uint16_t *)(this + index * 0x44 + 0x40) = rumbleValue;
        }
    }
}