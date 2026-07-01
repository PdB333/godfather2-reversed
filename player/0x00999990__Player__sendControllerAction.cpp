// FUNC_NAME: Player::sendControllerAction
// Address: 0x00999990
// Role: Sends a controller action event to the InputDeviceManager singleton.
// The local struct contains action ID (2), value (16), and controller index (0).
// This is likely a button press or axis event queued for processing.

void Player::sendControllerAction() {
    // Obtain the InputDeviceManager singleton instance.
    InputDeviceManager* inputMgr = InputDeviceManager::getInstance(); // FUN_009c8f80

    // Build an action structure on the stack.
    // +0x00: actionId (e.g., button press type)
    // +0x04: value (e.g., button mask or magnitude)
    // +0x08: controllerIndex (0 = first controller)
    struct ControllerAction {
        int actionId;      // offset 0x00
        int value;         // offset 0x04
        int controllerIdx; // offset 0x08
    } action = { 2, 0x10, 0 };

    // Call the first virtual function of InputDeviceManager (likely submitAction or queueEvent)
    // passing 'this' (the Player instance) and a pointer to the action struct.
    (inputMgr->vtable->submitAction)(this, &action);
}