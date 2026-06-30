// FUNC_NAME: initializeSlots
void initializeSlots(uint count)
{
    uint idx = 0;
    if (count != 0) {
        do {
            byte slotData = getSlotData(idx);   // Retrieves data for slot index (FUN_00b93170)
            applySlotData(slotData);            // Processes the slot data (FUN_0049b940)
            idx++;
        } while (idx < count);
    }
}