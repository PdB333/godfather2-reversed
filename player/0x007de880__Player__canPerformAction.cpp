// FUNC_NAME: Player::canPerformAction
// Address: 0x007de880
// Checks whether the player can perform a specific action (actionId from 0x13 to 0x17).
// Uses internal state at this+0x58 (m_pCharacterData) and various global game state checks.

bool __thiscall Player::canPerformAction(Player* this, uint param_2, uint param_3, int actionId, uint param_5) {
    bool result = false;
    // Pointer to character data block (e.g. PlayerData structure)
    char* pCharData = *(char**)(this + 0x58); // +0x58: m_pCharacterData
    uint charFlags1 = *(uint*)(pCharData + 0x24a0); // +0x24a0: bitfield flags (bit 20 = some lock)
    uint charFlags2 = *(uint*)(pCharData + 0x24a4); // +0x24a4: bitfield flags (bit 5 = some condition)

    switch (actionId) {
        case 0x13: // action: e.g. Interact
        {
            // Check global condition (maybe if player is in a specific state)
            if (FUN_00481640() != 0) {
                return (*(char*)(pCharData + 0x21ec) == '\0'); // +0x21ec: flag (e.g. m_bIsInteracting)
            }
            break;
        }
        case 0x14: // action: e.g. Attack
        case 0x15: // action: e.g. Aim
        {
            // If bit 20 of charFlags1 is set, action is not allowed
            if ((charFlags1 >> 0x14) & 1) {
                return false;
            }
            uint actionSubId = (actionId == 0x14) ? 0x3b : 0x3c; // Sub-action constants (e.g. 59, 60)
            // Query whether the sub-action state is active
            uint statePtr = FUN_00798f50(actionSubId); // e.g. GetStateMachineState
            if (FUN_0079e970(statePtr) != 0) {
                result = FUN_007de570(); // e.g. IsActionAvailableInCurrentContext
            }
            break;
        }
        case 0x16: // action: e.g. EnterVehicle
        {
            // If bit 5 of charFlags2 is clear, do additional checks
            if (!((charFlags2 >> 5) & 1)) {
                // Check game state flag 0x1e (30) – e.g. isPlayerInCutscene
                if (FUN_00690210(0x1e) != 0) {
                    return false;
                }
                // Check two manager states (e.g. PlayerVehicleManager)
                void* mgr1 = FUN_007ab130(); // e.g. GetVehicleManager
                if ( (*(uint*)((char*)mgr1 + 4) & 4) != 0 ) {
                    void* mgr2 = FUN_007ab160(); // e.g. GetPlayerVehicle
                    if ( (*(uint*)((char*)mgr2 + 4) & 4) != 0 ) {
                        return false;
                    }
                }
            }
            return true;
        }
        case 0x17: // action: e.g. ExitVehicle
        {
            void* mgr1 = FUN_007ab130();
            if ( (*(uint*)((char*)mgr1 + 4) & 4) != 0 ) {
                void* mgr2 = FUN_007ab160();
                if ( (*(uint*)((char*)mgr2 + 4) & 4) != 0 ) {
                    // Check game state flag 0x45 (69) – e.g. isPlayerExiting
                    if (FUN_00690210(0x45) == 0) {
                        return true;
                    }
                }
            }
            break;
        }
        default:
            // Fallback to generic action handler
            result = FUN_007ab790(param_2, param_3, actionId, param_5);
    }
    return result;
}