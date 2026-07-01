// FUNC_NAME: InputDeviceManager::checkForNewConnections
void __thiscall InputDeviceManager::checkForNewConnections(int *this) {
    char cVar1;
    int count;
    uint *slotData;
    uint slotIndex;
    uint maxSlots;

    slotIndex = 0;
    count = (*(code **)(*this + 0x220))(); // virtual call: getNumSlots()
    if (count != 0) {
        while (true) {
            slotData = (uint *)getSlotData(slotIndex); // FUN_0055d860
            if ((*slotData & 0x8000) != 0) // bit 15 = connected flag
                break;
            slotIndex = slotIndex + 1;
            maxSlots = (*(code **)(*this + 0x220))(); // re-fetch count (unusual)
            if (maxSlots <= slotIndex)
                return;
        }
        onControllerConnected(); // FUN_0087a9b0
        if ((((uint)this[0x322] >> 2 & 1) == 0) && // bit 2 of flags at +0xC88
            (*(int **)(DAT_012233a0 + 4) != 0) && // global game state pointer
            (*(int **)(DAT_012233a0 + 4) != 0x1f30)) { // not in a specific mode (e.g., menu)
            cVar1 = isGameActive(); // FUN_007f47a0
            if (cVar1 == '\0') {
                resetControllerState(this + 0xf); // FUN_004088c0, offset 0x3C
            }
        }
    }
    return;
}