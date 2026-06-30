// FUNC_NAME: InputManager::processControllerUpdates
void InputManager::processControllerUpdates()
{
    uint16_t count = *(uint16_t *)(this + 0x0C); // number of controller slots
    uint32_t i = 0;
    if (count != 0) {
        do {
            // Pointer array at +0x04 (each entry is a controller object)
            Controller* controller = *(Controller**)(this + 0x04 + i * 4);
            // Flags array at +0x20C (byte per slot)
            byte flag = *(byte*)(this + 0x20C + i);
            int32_t callArg;
            if ((flag & 1) == 0) {
                if (controller != nullptr) {
                    callArg = 1;
                    goto CALL_VIRTUAL;
                }
                // If flag==0 and controller==nullptr: callArg uninitialized? Retain original logic
            } else {
                callArg = 0;
            }
CALL_VIRTUAL:
            // Call first virtual function on the controller object with callArg (0 or 1)
            (**(code **)*controller)(callArg);
            i++;
        } while (i < count);
    }
    // Call post-update method (offset 0x00482830)
    this->postUpdateDevices();
}