// FUNC_NAME: EntityManager::registerEntry
void __thiscall EntityManager::registerEntry(int param_1, int someId)
{
    uint slotIndex = getSlotIndex(someId);
    if (slotIndex > 19) {
        int slot = 0;
        byte* flagsPtr = (byte*)(param_1 + 0x2c);
        while ((*flagsPtr & 1) != 0) {
            slot++;
            flagsPtr += 0x30;
            if (slot > 19) {
                return;
            }
        }
        initializeEntry(someId);
        onEntryAdded();
    }
    return;
}