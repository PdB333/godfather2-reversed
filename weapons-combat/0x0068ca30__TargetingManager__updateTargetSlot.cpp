// FUNC_NAME: TargetingManager::updateTargetSlot
void __thiscall TargetingManager::updateTargetSlot(TargetingManager* this) {
    byte slotIndex = *(byte*)((int)this + 0x14); // current slot index (0..15)
    if (slotIndex < 0x10) {
        float threshold = *(float*)(DAT_01223464 + 0x1694); // global squared distance threshold (e.g., maxTargetDist)
        float thresholdSq = threshold * threshold;
        TargetData* target = (TargetData*)FUN_00410540(slotIndex); // get target data for this slot
        if (target != nullptr && *(byte*)((int)target + 0x3e) != '\0') { // target enabled/active flag
            if ( (*(uint*)((int)target + 0x10) & 0x3fff) != 0 || // check if some bitmask flags indicate availability
                 (thresholdSq <= (target->posX * target->posX + target->posY * target->posY) ||
                  thresholdSq <= (target->posZ * target->posZ + target->posW * target->posW)) ) {
                *(int*)((int)this + 0x30) = DAT_01205210; // set member (e.g., selectedTargetId)
            }
        }
    }
}