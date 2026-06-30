// FUNC_NAME: InputDeviceManager::processControllerPacket
void __thiscall InputDeviceManager::processControllerPacket(void *this) {
    ControllerData *pData;      // pointer to input data buffer
    Controller *pController;    // found controller object

    // Dereference this+0x8 to get the data buffer
    pData = *(ControllerData **)((char *)this + 8);

    // Validate the buffer's type field (short at offset 0x2 must be 0x44)
    if (pData->type != 0x44) {
        // Type mismatch – call debug break via global pointer
        (*(code **)(*DAT_01205590 + 4))();
    }

    // Retrieve the controller object for the slot index stored at offset 0x4
    pController = (Controller *)GetControllerBySlot(this, pData->slotIndex);
    if (pController == (Controller *)0x0) {
        // No such controller – error
        (*(code **)(*DAT_01205590 + 4))();
        return;
    }

    // Call virtual function at vtable offset 0x24 with three sub‑buffers:
    //   - first: pData + 0x8
    //   - second: pData + 0x18
    //   - third: pData + 0x38
    (*(code **)(*(int *)pController + 0x24))(
        (char *)pData + 8,
        (char *)pData + 0x18,
        (char *)pData + 0x38);
}