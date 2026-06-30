// FUNC_NAME: SlotStateManager::updateSlotState
void SlotStateManager::updateSlotState(int slotIndex, int newValue1, int newValue2) {
    // Global array of state pairs (two ints per slot)
    // sStateSlots is likely defined as: static int sStateSlots[/*maxSlots*2*/];
    if ((sStateSlots[slotIndex * 2] == newValue1) && (sStateSlots[slotIndex * 2 + 1] == newValue2)) {
        // Already in desired state; just signal completion with urgency level
        // slotIndex==4 is a special case (maybe "forced" or "critical")
        Internal::handleStateComplete((slotIndex == 4) + 1);  // returns 2 for slot 4, else 1
        return;
    }
    // Otherwise, transition from old first value to new first value
    Internal::transitionState(sStateSlots[slotIndex * 2], newValue1);
}