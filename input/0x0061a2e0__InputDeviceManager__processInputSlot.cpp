// FUNC_NAME: InputDeviceManager::processInputSlot
bool __thiscall CInputDeviceManager::processInputSlot(int thisPtr, int slotIndex, int subIndex, char* outActionTaken)
{
    *outActionTaken = 0;
    if (slotIndex >= 0x1000) {
        return false;
    }
    InputSlot* slot = &g_inputSlotArray[slotIndex];
    if (slot == nullptr) {
        return false;
    }
    if (slot->dataPtr == nullptr) {
        return false;
    }
    if (slot->state > 1) {
        // Already active – check if data object is in state 3
        if (*(int*)((uint8_t*)slot->dataPtr + 8) == 3) {
            return true;
        }
        return false;
    }

    if (FUN_00619f90() != 0) {
        // Read TLS slot 0 (global per-thread flag)
        int* tlsArray = (int*)__readfsdword(0x2C); // TLS array base
        int* tlsSlot0 = (int*)*tlsArray;          // first TLS slot
        int modeFlag = *(tlsSlot0 + 0x34 / 4);    // offset 0x34
        if (modeFlag == 0) {
            FUN_00619ef0(slotIndex, subIndex, thisPtr);
            *outActionTaken = 1;
            return true;
        } else {
            FUN_00606ac0();
            *outActionTaken = 1;
            return true;
        }
    }
    return false;
}