// FUNC_NAME: AudioSlotManager::allocateSoundSlot

int __thiscall AudioSlotManager::allocateSoundSlot(AudioSlotManager* this, const AudioSlotRequest* request)
{
    int chosenSlot = -1;
    bool slotMarked[5] = {false, false, false, false, false}; // acStack_1c

    if (request->isActive != false) {
        // ---- First pass: check if the same sound ID is already active in a slot not in state 3 ----
        for (int i = 0; i < 5; i++) {
            Slot* slot = &this->slots[i];
            if (slot->id != 0 && slot->state != 3 && slot->id == request->soundId) {
                if (request->timestamp < slot->timestamp) {
                    debugLogSound(request->soundId);  // FUN_005dbc10(request->soundId)
                    return -1;  // Existing entry is newer, reject this request
                }
                slotMarked[i] = true;  // Mark slot for potential update
            }
        }

        // ---- Second pass: for each marked slot, stop it and clear its state ----
        for (int i = 0; i < 5; i++) {
            Slot* slot = &this->slots[i];
            if (slotMarked[i]) {
                debugLogSoundSlot(request->soundId, i, slot->id); // FUN_005dbc10(request->soundId, i, slot->id)
                float elapsed = slot->timer; // local_10 = pfVar6[0]
                // ... some setup (local_14 = 1, local_c = 0, local_8 = 0)
                // Probably called updateTimer or similar
                // FUN_005e9440();
                if (elapsed == someGlobalThreshold) { // DAT_00e2b05c
                    // Stop the slot twice (could be for fadeout)
                    FUN_005e86e0(slot); // first stop
                    FUN_005e86e0(slot); // second stop
                    slot->field200 = 0.0f; // pfVar6[-0xc]
                    slot->field204 = 0.0f; // pfVar6[-0xb]
                }
            }
        }
    }

    // ---- Find an empty slot (first inactive slot) and count active slots ----
    bool slot0Active = this->slots[0].active;
    if (slot0Active == false) {
        chosenSlot = 0;
    }
    uint activeCount = slot0Active ? 1 : 0;

    if (this->slots[1].active == false) {
        if (chosenSlot == -1) chosenSlot = 1;
    } else {
        activeCount++;
    }

    if (this->slots[2].active == false) {
        if (chosenSlot == -1) chosenSlot = 2;
    } else {
        activeCount++;
    }

    if (this->slots[3].active == false) {
        if (chosenSlot == -1) chosenSlot = 3;
    } else {
        activeCount++;
    }

    if (this->slots[4].active == false) {
        if (chosenSlot == -1) chosenSlot = 4;
    } else {
        activeCount++;
    }

    // If we found an empty slot, but the number of active slots is less than the max allowed, proceed
    if (activeCount < this->maxActiveSlots) {
        // fall through to LAB_005e2859
    } else {
        chosenSlot = -1; // Too many active slots, must steal
    }

    // ---- If no slot chosen yet, try to steal one ----
    if (chosenSlot == -1) {
        debugLog(); // FUN_005dbc10()
        chosenSlot = tryStealSlot(this, request); // FUN_005e29b0()
        if (chosenSlot == -1) {
            // Fallback: pick the active slot with the oldest timestamp less than the request timestamp
            if (this->slots[0].active != false && this->slots[0].timestamp < request->timestamp) {
                chosenSlot = 0;
            }
            if (this->slots[1].active != false && this->slots[1].timestamp < request->timestamp &&
                (chosenSlot == -1 || this->slots[1].timestamp < this->slots[chosenSlot].timestamp)) {
                chosenSlot = 1;
            }
            if (this->slots[2].active != false && this->slots[2].timestamp < request->timestamp &&
                (chosenSlot == -1 || this->slots[2].timestamp < this->slots[chosenSlot].timestamp)) {
                chosenSlot = 2;
            }
            if (this->slots[3].active != false && this->slots[3].timestamp < request->timestamp &&
                (chosenSlot == -1 || this->slots[3].timestamp < this->slots[chosenSlot].timestamp)) {
                chosenSlot = 3;
            }
            if (this->slots[4].active != false && this->slots[4].timestamp < request->timestamp &&
                (chosenSlot == -1 || this->slots[4].timestamp < this->slots[chosenSlot].timestamp)) {
                chosenSlot = 4;
            }

            if (chosenSlot == -1) {
                return -1;  // Could not find any slot to steal
            }

            // ---- Reset the chosen stolen slot ----
            Slot* chosen = &this->slots[chosenSlot];
            // FUN_005e9440() with args: local_14=1, local_c=0, local_8=0, local_10=0.0
            // probably a timer reset call
            // FUN_005e86e0() twice (fadeout)
            chosen->resetField1 = 0;   // *(int*)(slotBase + 0x1fc) = 0
            chosen->resetField2 = 0;   // *(int*)(slotBase + 0x200) = 0
        }
    }

    return chosenSlot;
}