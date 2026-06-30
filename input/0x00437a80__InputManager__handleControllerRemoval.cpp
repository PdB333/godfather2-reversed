// FUNC_NAME: InputManager::handleControllerRemoval
// Address: 0x00437a80
// Called when a controller is disconnected (eventType == 2)
// Uses global controller slot array (gControllerSlotArray) at 0x012233f0
// Each slot is 0x44 bytes; offset +8 is a pointer to a ControllerDevice object
void InputManager::handleControllerRemoval(uint slotIndex, int eventType)
{
    // Only for slots 0 and 1, and only on disconnect event (2)
    if ((slotIndex >= 2) || (eventType != 2))
        return;

    // Offset into the slot array (0x44 per slot)
    uint slotOffset = slotIndex * 0x44;
    int* slotBase = reinterpret_cast<int*>(gControllerSlotArray + slotOffset);

    // +8: pointer to ControllerDevice object
    int* controllerDevice = reinterpret_cast<int*>(slotBase[8 / 4]);
    if (controllerDevice == nullptr)
        return;

    // +0xc: some buffer or state pointer in the slot
    int* slotPlus12 = slotBase + (0xc / 4);
    // ClearBuffer or release something on the device
    ClearDeviceBuffer(controllerDevice, slotPlus12);

    // +0x40: some internal pointer in the ControllerDevice
    int* deviceInternal = reinterpret_cast<int*>(controllerDevice + (0x40 / 4));
    // +8: another pointer in the device (maybe a stack pointer)
    int* stackPtr = reinterpret_cast<int*>(controllerDevice[8 / 4]);
    int stackOffset = -8; // adjust back by 8 bytes
    // PopFromStack? (called with parameters: device, device+0x40, stackPtr+offset, 0)
    PopControllerEvent(controllerDevice, deviceInternal, stackPtr + stackOffset, 0);

    // Manipulate stack pointer for the device
    int* currentStack = reinterpret_cast<int*>(controllerDevice[8 / 4]);
    int* stackTop = currentStack + (-8 / 4); // 2 ints back
    int* stackValues = reinterpret_cast<int*>(stackTop);
    // Write two ints at the stack top (probably event data)
    stackTop[0] = *stackValues;
    stackTop[1] = *(stackValues + 1);

    // After adjustment, check if the stack element type matches
    int* newStackPtr = reinterpret_cast<int*>(controllerDevice[8 / 4]);
    if ((reinterpret_cast<int*>(newStackPtr)[-2] == 6)) // type 6 = disconnect?
    {
        float slotAsFloat = static_cast<float>(static_cast<int>(slotIndex));
        // If slotIndex is negative (unlikely for uint), adjust
        if (static_cast<int>(slotIndex) < 0) {
            slotAsFloat += 0.0f; // DAT_00e44578 is probably 0.0 (unreferenced)
        }
        // Write type 3 and slot index as float
        reinterpret_cast<int*>(newStackPtr)[0] = 3; // event type?
        reinterpret_cast<float*>(newStackPtr)[1] = slotAsFloat;

        // Advance stack pointer by 8 bytes (2 ints)
        controllerDevice[8 / 4] += 8;

        // Build a local message structure
        int message[2];
        message[0] = reinterpret_cast<int*>(controllerDevice[8 / 4])[-4]; // stack -0x10?
        message[1] = 0;

        // Get the size of the message area
        int messageSize = message[0] - controllerDevice[0x1c / 4];

        // Dispatch the message using the global callback (LAB_006261e0)
        DispatchControllerMessage(reinterpret_cast<void*>(0x006261e0), message, messageSize);
    }

    // Clear the device pointer in the slot
    slotBase[8 / 4] = 0;
    // Clear some flag at +0xc
    *reinterpret_cast<char*>(slotBase + (0xc / 4)) = 0; // low byte

    // Update the player slot mapping (another global array)
    int* playerMap = reinterpret_cast<int*>(gPlayerSlotMap + 8 + slotIndex * 4);
    int* playerObject = reinterpret_cast<int*>(*playerMap);
    if (playerObject) {
        playerObject[0x20c / 4] = slotIndex; // store slot index at +0x20c
        playerObject[0x204 / 4] = 0;          // clear something at +0x204
    }
}