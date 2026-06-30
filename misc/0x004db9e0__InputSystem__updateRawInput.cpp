// FUNC_NAME: InputSystem::updateRawInput
void InputSystem::updateRawInput(void)
{
    // 64-byte buffer for raw input state (e.g., keyboard/mouse or XInput snapshot)
    byte rawInputBuffer[64];
    // Retrieve current device state handle or status
    uint32_t deviceStatus = FUN_004dbf10();
    // Process the device state into the buffer
    FUN_004dba00(rawInputBuffer, deviceStatus);
    return;
}