// FUNC_NAME: AnimationManager::updateSlots
void AnimationManager::updateSlots(float deltaTime)
{
    bool bHasHighPriority = false;
    int slotCount = getSlotCount(); // FUN_00579170
    AnimationSlot* prevSlot = nullptr;
    int i = 0;

    if (slotCount > 0) {
        do {
            // Round-robin: start from current offset, then cycle
            int slotIndex = (this->m_currentSlotBase - i + this->m_slotCount) % this->m_slotCount;
            AnimationSlot* slot = (AnimationSlot*)((int)this->m_slotsArray + slotIndex * sizeof(AnimationSlot)); // 0xe0

            // Decrement remaining time if positive
            if (slot->remainingTime > 0.0f) {
                slot->remainingTime -= deltaTime;
            }

            // If remaining time expired
            if (slot->remainingTime <= 0.0f) {
                float excessTime = (slot->accumulatedTime + deltaTime) - slot->remainingTime;
                slot->accumulatedTime = excessTime;
                slot->remainingTime = 0.0f;

                // If accumulated time exceeds total duration, clamp and mark finished
                if (slot->duration <= excessTime) {
                    slot->accumulatedTime = slot->duration;
                    slot->state = 0; // animation finished
                }
            }

            // Stop processing if this slot is finished (state == 0)
            if (slot->state == 0) break;

            // Determine whether to update this slot
            if (prevSlot == nullptr) {
                // Track high priority flags
                if (slot->priority == 1) {
                    bHasHighPriority = true;
                }
            } else if ((prevSlot->state != 0) && (prevSlot->priority == 1)) {
                // If previous slot is active and high priority, skip update? Actually the condition continues to update
                // Actually the logic: if prevSlot is finished OR prevSlot->priority != 1, then proceed to update
                // In code: if ((char)prevSlot->state == '\0') OR (prevSlot->priority != 1) then goto LAB_00578a81 (the update call)
                // So we invert: if prevSlot is active AND high priority, we skip update (i.e., don't call update? But code doesn't call update, it goes to next iteration)
                // Actually from the decompiled:
                // if (piVar3 == (int *)0x0) { ... update; }
                // else if (((char)piVar3[0x1c] == '\0') || (piVar3[0x20] != 1)) goto LAB_00578a81; // update
                // So if prevSlot != null and (prevSlot->state != 0) AND (prevSlot->priority == 1), then it does NOT go to update, meaning it skips updating current slot.
                // Our code mirrors that: if prevSlot != null and prevSlot is active and high priority, then we skip the update.
                // But note: the loop continues regardless of update being called? The update is called only if condition passes.
                // Actually the loop does i++ and piVar3 = piVar5 after the if-else, so it always advances.
                // So we need to conditionally call update.
                // Recreating:
                // if (prevSlot == null) { update; set bVar1; }
                // else if (prevSlot->state == 0 || prevSlot->priority != 1) { update; }
                // else { // prevSlot is active and high priority, skip update }
                // then i++, prevSlot = slot;
            }

            // Determine if we should update this slot
            bool shouldUpdate = false;
            if (prevSlot == nullptr) {
                shouldUpdate = true;
                if (slot->priority == 1) bHasHighPriority = true;
            } else if ((prevSlot->state == 0) || (prevSlot->priority != 1)) {
                shouldUpdate = true;
            }

            if (shouldUpdate) {
                // Call virtual update function at vtable+0x14
                (*(void (**)(AnimationSlot*, float))(*(int*)slot + 0x14))(slot, deltaTime);
            }

            i++;
            prevSlot = slot;
        } while (i < slotCount);
    }

    // If no high priority slot was processed, update the manager itself
    if (!bHasHighPriority) {
        (*(void (**)(AnimationManager*, float))(*(int*)this + 0x14))(this, deltaTime);
    }
}

// Internal helper to get slot count (calls FUN_00579170)
int AnimationManager::getSlotCount()
{
    // Implementation likely returns m_slotCount member
    return this->m_slotCount;
}