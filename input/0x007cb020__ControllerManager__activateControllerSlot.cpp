// FUNC_NAME: ControllerManager::activateControllerSlot
void __thiscall ControllerManager::activateControllerSlot(ControllerManager* thisPtr)
{
    // Dereference thisPtr+0x58 to get pointer to controller system data
    int controllerSystem = *(int*)(thisPtr + 0x58);
    // Access slot data at offset 0x1bc8 within controller system data
    int slotData = *(int*)(controllerSystem + 0x1bc8);

    // Enable two flags at offsets +0x5e1 and +0x5e3 (likely 'active' and 'connected' flags)
    *(byte*)(slotData + 0x5e1) = 1;
    *(byte*)(slotData + 0x5e3) = 1;

    // Clear input buffers for slot 0
    clearInputBuffers(0);
    // Reset input state for slot 0
    resetInputState(0);
}