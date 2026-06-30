// FUNC_NAME: ObjectManager::resetAllSlots
// Function at 0x0043c5d0 - Resets all 64 slots in the given context if either primary (+0x148) or secondary (+0x14c) activation flag is set.
// Called from 0x0046ea20 (likely during initialization).
// __thiscall: this passed in EAX, one explicit parameter (param_1 = pContext)
void ObjectManager::resetAllSlots(void* pContext) {
    // Check if either the primary or secondary activity indicator is non-zero.
    // Offsets: +0x148 (likely pointer or flag for primary activity),
    //          +0x14c (likely pointer or flag for secondary activity).
    if (this->field_0x148 != 0 || this->field_0x14c != 0) {
        // Loop over all 64 slots (0x40).
        for (uint32_t i = 0; i < 0x40; i++) {
            // Call function at 0x0043c4e0 to reset individual slot.
            // This likely clears or reinitializes slot `i` within the context pointed by pContext.
            resetSingleSlot(pContext, i);
        }
    }
}