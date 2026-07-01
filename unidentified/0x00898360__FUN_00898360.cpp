// FUNC_NAME: SomeManager::initializeSlots
void SomeManager::initializeSlots(int param_1)
{
    uint slotIndex = 0;
    do {
        initializeSlot(param_1, slotIndex); // FUN_008982e0, initializes a single slot
        slotIndex = slotIndex + 1;
    } while (slotIndex < 7);
    return;
}