//FUNC_NAME: ControllerManager::updateControllerState
void __thiscall ControllerManager::updateControllerState(int controllerIndex)
{
    char stateBuffer[60];   // +0x00: buffer for controller state data (60 bytes)
    char outputBuffer[16];  // +0x00: buffer for output/cleared state (16 bytes)

    // Read raw controller state into buffer
    readControllerState(controllerIndex, stateBuffer);

    // Process the state (e.g., map to game actions)
    processControllerState(stateBuffer);

    // Check a flag at offset 0xd8 from a component pointer stored at this+0x18
    // If the byte equals 0x07 (bell character), trigger a debug/log action
    if (*(char*)(*(int*)(this + 0x18) + 0xd8) == '\a')
    {
        setDebugFlag(1, 1, 0);
    }

    // Clear or finalize the output buffer
    clearControllerState(outputBuffer);
}