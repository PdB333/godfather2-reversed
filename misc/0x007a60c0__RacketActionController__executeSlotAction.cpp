// FUNC_NAME: RacketActionController::executeSlotAction
bool __thiscall RacketActionController::executeSlotAction(int this[0x1000], int slotType)
{
    // Check if game is paused or in cutscene
    if (isGamePaused() || isInCutscene()) {
        return false;
    }

    if (slotType == 1) {
        // Slot 1: Primary action
        if (this[0x924] == 1) {
            return false; // Already active slot 1
        }

        // Check if any resources are available for slot 1
        if ((this[0xa42] == 0) && (this[0xa43] == 0) && (this[0xa44] == 0) && (this[0xa45] == 0)) {
            return false; // No resources
        }

        // Check if slot 1 data is valid
        if ((this[0xa47] == 0) && (this[0xa48] == 0) && (this[0xa49] == 0) && (this[0xa4a] == 0)) {
            return false; // Slot 1 data not ready
        }

        // Consume resources for slot 1
        int* slot1Resources = &this[0xa42];
        if (!consumeResources(slot1Resources)) {
            return false; // Resource consumption failed
        }

        playSound(SOUND_UI_CLICK);          // FUN_004086d0(&DAT_01206970)
        clearInputState();                  // FUN_00460d90()

        // Activate slot 1 (this at offset 0xa47 points to slot1 data)
        (this->vftable->playSlotAnimation)(&this[0xa47], 1);  // vtable+0x184
    }
    else if (slotType == 2) {
        // Slot 2: Secondary action
        if (this[0x924] == 2) {
            return false; // Already active slot 2
        }

        // Check if any resources are available for slot 2
        if ((this[0xa4b] == 0) && (this[0xa4c] == 0) && (this[0xa4d] == 0) && (this[0xa4e] == 0)) {
            return false; // No resources
        }

        if (isInMenu()) {
            return false; // Prevent activation while in menu
        }

        // Consume resources for slot 2
        int* slot2Resources = &this[0xa4b];
        if (!consumeResources(slot2Resources)) {
            return false;
        }

        playSound(SOUND_UI_CLICK);
        clearInputState();

        // Activate slot 2 (this at offset 0xa4f points to slot2 data)
        (this->vftable->playSlotAnimation)(&this[0xa4f], 1);  // vtable+0x184
    }
    else {
        return false; // Invalid slot type
    }

    // Common post-activation sequence
    (this->vftable->onSlotActivated)(slotType);         // vtable+0xf0
    (this->m_renderer->vftable->refreshLayout)();        // this[0x4c] -> vtable+0x2c
    (this->vftable->redraw)();                           // vtable+0x70
    (this->m_renderer->vftable->refreshLayout)();        // again
    (this->vftable->setState)(1);                        // vtable+0x134
    refreshUIState();                                    // FUN_007fb040()
    setUIClickFlag(1);                                   // FUN_007a4250(1)
    (this->vftable->finalizeAction)();                   // vtable+0x2dc

    // Notify game instance
    GameInstance* game = getGameInstance(DAT_01131010);  // FUN_0043b870(DAT_01131010)
    (game->vftable->onRacketActionExecuted)(this);       // vtable+0x1c

    return true;
}