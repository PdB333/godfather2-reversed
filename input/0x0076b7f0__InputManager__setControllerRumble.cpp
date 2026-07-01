// FUNC_NAME: InputManager::setControllerRumble
void InputManager::setControllerRumble(int controllerIndex, char enableRumble)
{
    // Each controller slot is 0x2C bytes (44 bytes) in the controller data array
    int slotOffset = controllerIndex * 0x2C;
    
    if (enableRumble != '\0') {
        // Enable rumble - use the "on" rumble values (stored at +0x24 offset from slot base)
        FUN_0076b680(
            *(undefined4 *)(&DAT_00d65db4 + slotOffset),  // +0x24: left motor speed
            *(undefined4 *)(&DAT_00d65db8 + slotOffset),  // +0x28: right motor speed
            *(undefined4 *)(&DAT_00d65dbc + slotOffset),  // +0x2C: duration
            *(undefined4 *)(&DAT_00d65dc0 + slotOffset),  // +0x30: start delay
            *(undefined4 *)(&DAT_00d65dc4 + slotOffset)   // +0x34: fade time
        );
        return;
    }
    
    // Disable rumble - use the "off" rumble values (stored at +0x10 offset from slot base)
    FUN_0076b680(
        *(undefined4 *)(&DAT_00d65da0 + slotOffset),  // +0x10: left motor speed (0)
        *(undefined4 *)(&DAT_00d65da4 + slotOffset),  // +0x14: right motor speed (0)
        *(undefined4 *)(&DAT_00d65da8 + slotOffset),  // +0x18: duration (0)
        *(undefined4 *)(&DAT_00d65dac + slotOffset),  // +0x1C: start delay (0)
        *(undefined4 *)(&DAT_00d65db0 + slotOffset)   // +0x20: fade time (0)
    );
}