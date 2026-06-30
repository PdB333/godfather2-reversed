// FUNC_NAME: Player::interactWith
uint Player::interactWith(Entity* target)
{
    // Profiling scope 0xCB
    EA_PROFILE_ENTER(0xCB);

    // Check if we can interact: not disabled, target exists, target not self, and global interaction allowed
    if ((((this->flags0x8E8 >> 0x1B & 1) == 0) || (target == nullptr) || (target == this)) ||
        (FUN_007f4800() == false)) {
        goto LAB_EXIT;
    }

    // Attempt to cast target to various types using RTTI hashes
    BaseVehicle* vehicle = dynamicCast<BaseVehicle>(target, 0x383225a1); // hash for BaseVehicle?
    if (vehicle != nullptr) {
        // --- Target is a vehicle ---
        float speed = vehicle->getSpeed(); // vtable+0xBC
        uint eventId = 0x259f3b7f; // default for speed > 0
        if (speed == 0.0f) {
            eventId = 0x259f3b7f; // (actually same? Wait: code sets 0xdee17027 if speed != 0, else 0x259f3b7f)
        }
        else {
            eventId = 0xdee17027; // from code: uStack_24 set to 0xdee17027 initially, then to 0x259f3b7f if fVar8 == 0
        }
        // Actually the code: fVar8 = speed; uStack_24 = 0xdee17027; if (fVar8 == 0) uStack_24 = 0x259f3b7f;
        // So if speed==0, eventId=0x259f3b7f; else eventId=0xdee17027
        FUN_006ada80(0, -1); // Activate something (maybe interaction state)
        FUN_0044b210(vehicle); // Disable the vehicle's AI?
        Vector3 pos;
        getPosition(&pos); // vtable+0x4C
        pos.y = 0; // zero out something? Actually we capture local_40 from param_1+0xF and set uStack_3c=0
        // The code: local_40 = &something, then set uStack_3c=0, then call a func with stack pointer? This is awkward.
        // Reconstructing: getMemberVector(&pos, this + 0xF); // offset 0xF from this? That seems like a vector member.
        // Then call FUN_00408bf0 which might be a string copy or something.
        bool isBusy = this->isBusy(); // vtable+0x28C
        if ((isBusy == false) && 
            (FUN_00690150(0x30) == false) && // maybe isInCompelling?
            (FUN_00690210(0x48) == false))   // maybe isInCombat?
        {
            int rangeCheck = FUN_006ad7f0(vehicle); // Check if in range
            bool lineOfSight = false;
            if ((rangeCheck != 0) && (FUN_009a9460() != 0)) {
                lineOfSight = true;
            }
            uint param3 = 0;
            uint param4 = FUN_006fbc40(0, 0); // Some resource/flag
            uint eventIdFinal;
            if (!lineOfSight) {
                eventIdFinal = 0x6fc3a756; // event for no LOS
            } else {
                eventIdFinal = 0x7b6d7d3b; // event for LOS
            }
            // Send event
            FUN_007f96a0(eventIdFinal, 0, param4, param3);
            FUN_006fbc70(); // End resource acquisition
        }
        // Additional check and flag setting
        int someState = FUN_007f41e0();
        if (someState != 0) {
            FUN_004abc20(0x80); // Play animation/sound
        }
        FUN_006ccd30(vehicle); // Start interaction/dialogue
        this->flags0x1F58 |= 4; // Mark interaction started
        FUN_006ad490(); // Notify completion
    }
    else {
        // --- Target is not a vehicle ---
        Sentient* sentient = dynamicCast<Sentient>(target, 0x55859efa); // hash for Sentient?
        if (sentient != nullptr) {
            // Target is a sentient
            if ((*(int**)DAT_012233a0 + 4) == nullptr || (*(int**)DAT_012233a0 + 4) == 0x1f30) {
                // No global flag: use default (maybe global player state)
                bool canInteract = false;
            }
            else {
                canInteract = FUN_00690210(0x48); // isInCombat?
            }
            bool isPlayerPerforming = this->isPerformingAction(); // vtable+0x1BC
            if ((isPlayerPerforming) &&
                (Character* character = dynamicCast<Character>(target, 0x369ac561); character != nullptr) &&
                (character->isPerformingAction() == true) && // vtable+0x1BC on character
                (FUN_0072f180(character) == true) && // Additional check (maybe canBeInteracted)
                (canInteract == false)) // If player is not in combat
            {
                uint param1 = 0;
                uint param2 = FUN_006fbc40(0, 0);
                // Send interaction event
                FUN_007f96a0(0x14ea613a, 0, param2, param1);
                FUN_006fbc70();
            }
            // Another check
            bool inStealth = FUN_00690150(0x44); // isInStealth?
            if (inStealth) {
                int someGlobal = FUN_007f41e0();
                if (someGlobal != 0) {
                    FUN_004abc20(0x80); // Play stealth animation
                }
                FUN_006ccd30(sentient); // Start stealth takedown
            }
        }
        else {
            // Target is neither vehicle nor sentient - possibly a generic interactable
            if ((FUN_007f7c50() == false) && // Global cutscene check
                (Interactable* interactable = dynamicCast<Interactable>(target, 0x63c15f4e); interactable != nullptr) &&
                (this->canInteract(1) == false)) { // vtable+0x?? maybe AICarBehavior? Actually this method is FUN_00795a90 with param1=1
                // Compute distance to interactable
                Vector3 pos;
                getPosition(&pos); // vtable+0x4C
                float distance = computeDistance(&pos); // FUN_0046cb10
                setInteractionDistance(this, distance); // FUN_00796ba0
            }
        }
    }

    // Final common check: if target is the same as a certain stored object (like current interaction target)
    Entity* currentInteractTarget = nullptr;
    if (this->currentInteractionPtr != 0) {
        currentInteractTarget = (Entity*)(this->currentInteractionPtr - 0x48); // offset to container
    }
    if (target == currentInteractTarget) {
        this->flags0x1F58 |= 0x200; // Mark as "being interacted with"
    }

LAB_EXIT:
    uint profileResult = EA_PROFILE_LEAVE(0xCB);
    return profileResult & 0xFFFFFF00; // Return high part (maybe profiler value)
}