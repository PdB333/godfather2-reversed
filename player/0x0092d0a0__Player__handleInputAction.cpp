// FUNC_NAME: Player::handleInputAction
// Address: 0x0092d0a0
// Handles input actions from player controller, dispatching to current state handler
// Based on decompilation: processes action ID and current player state/queue

int __thiscall Player::handleInputAction(int actionId) {
    int context1 = getInputContext1(); // FUN_00466840
    int local_c;
    int local_8;
    char local_4;

    if (actionId != context1) {
        int context2 = getInputContext2(); // FUN_00466860
        if (actionId != context2) {
            switch (actionId) {
                case 0: // Accept/Confirm
                    return 1;
                case 2: // Cancel
                    setUISelection(-1); // FUN_0092cc10(0xffffffff)
                    break;
                case 4: // Start/Menu
                    setUISelection(1); // FUN_0092cc10(1)
                    return 0;
                case 8: // Move Up
                    sendUIMessage("MoveUp", &globalStructA, &globalVec1, &globalVec2); // FUN_00929a20
                    return 0;
                case 9: // Move Down
                    sendUIMessage("MoveDown", &globalStructA, &globalVec1, &globalVec2);
                    return 0;
                case 0xC: // Action/Attack
                    triggerAction(4, 0); // FUN_00922e20(4,0)
                    return 0;
            }
            return 0;
        }
        // Handle context2 input
        ((void (__thiscall *)(Player*))this->vtable[0x2c])(); // Call virtual update function at vtable+0x2c
        local_c = globalVec3; // DAT_01130310
        local_8 = 0;
        local_4 = 0;
        setVec3((Vec3*)&local_c, 0); // FUN_00408a00
        return 0;
    }

    // Context1 input handling (main gameplay actions)
    int currentState = this->field_0x5C; // +0x5C
    if ((currentState == 0) && ((unsigned int)this->field_0xF8 < (unsigned int)this->field_0xFC)) { // +0xF8, +0xFC
        if (this->field_0x64 != 0) { // +0x64 (isBusy)
            processIdleAction(); // FUN_0092cac0
            return 0;
        }
    } else {
        if (currentState == 3) {
            char canProceed = checkCombatCondition(); // FUN_0090a8c0
            if (canProceed != 0) {
                return 0;
            }
            startCombatAction(); // FUN_0092be60
            return 0;
        }
        if ((currentState != 1) || (this->field_0x50 != 0)) { // +0x50 (pendingActionFlag)
            // Invalid state or pending action - reset
            local_8 = 0;
            local_4 = 0;
            local_c = globalVec2; // DAT_011302c0
            setVec3((Vec3*)&local_c, 0);
            return 0;
        }
        // State 1 with no pending action
        int attackMode = this->field_0x134; // +0x134
        if (attackMode != 1) {
            if (attackMode != 3) {
                clearDebugVector(&globalVec2, 0); // FUN_00402050
                return 0;
            }
            startRangedAttack(); // FUN_0092ae80
            return 0;
        }
        // attackMode == 1 (melee)
        if (this->field_0x64 != 0) { // +0x64 (isBusy)
            startMeleeAction(); // FUN_0092cb20
            return 0;
        }
    }
    // Default fallback
    processDefaultAction(); // FUN_0092bdd0
    return 0;
}