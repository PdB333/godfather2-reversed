// FUNC_NAME: InputDeviceManager::readThumbstick

void __thiscall InputDeviceManager::readThumbstick()
{
    // Get the currently active controller slot index (e.g., player 0-3)
    int slot = getActiveControllerSlot(); // FUN_0060d850

    // Get pointer to raw controller state structure (likely includes thumbstick data as ushorts)
    uint16_t* rawState = (uint16_t*)getControllerState(slot); // FUN_00606370

    // Read X and Y thumbstick values from offsets +0x02 and +0x04
    // These are unsigned short raw axis values (0-65535) converted to float
    this->thumbstickX = (float)rawState[1]; // +0x02
    this->thumbstickY = (float)rawState[2]; // +0x04
}