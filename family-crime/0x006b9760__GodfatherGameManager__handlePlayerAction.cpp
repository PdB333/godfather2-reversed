// FUNC_NAME: GodfatherGameManager::handlePlayerAction
int __fastcall GodfatherGameManager::handlePlayerAction(ActionCommand* cmd)
{
    // cmd: pointer to action command structure
    // +0x6c: actionId (uint, 1-based)
    // +0x70: actionArg (uint, parameter for certain actions)

    // Get the global player data (likely a singleton manager)
    PlayerData* playerData = GodfatherGameManager::getPlayerData();  // FUN_006b96a0
    int result = 0;
    if (playerData != 0) {
        int actionIndex = cmd->actionId - 1;  // +0x6c - 1
        result = (int)playerData; // initial result is the pointer (but probably unused)
        switch(actionIndex) {
        case 0:
            // Action 1: Start aiming
            result = PlayerInputHandler::startAiming(cmd->actionArg);  // FUN_006b30c0
            return result;
        case 1:
            // Action 2: Stop aiming
            result = PlayerInputHandler::stopAiming();  // FUN_006b3100
            return result;
        case 2:
            // Action 3: Start firing
            result = PlayerInputHandler::startFiring(cmd->actionArg);  // FUN_006b3160
            return result;
        case 3:
            // Action 4: Stop firing
            result = PlayerInputHandler::stopFiring();  // FUN_006b3190
            return result;
        case 4:
            // Action 5: Start grapple/takedown
            result = PlayerInputHandler::startGrapple();  // FUN_006b5ac0
            return result;
        case 5:
            // Action 6: Stop grapple/takedown
            result = PlayerInputHandler::stopGrapple();  // FUN_006b5b10
            return result;
        case 6:
            // Action 7: Clear cover flag (bit6 of playerData->flags)
            playerData->flags &= ~0x40;  // +0x34
            return result;
        case 7:
            // Action 8: Set cover flag
            playerData->flags |= 0x40;
            return result;
        case 8:
            // Action 9: Clear sprint flag (bit7)
            playerData->flags &= ~0x80;
            return result;
        case 9:
            // Action 10: Set sprint flag
            playerData->flags |= 0x80;
            return result;
        case 10:
            // Action 11: Clear aiming flag (bit11)
            playerData->flags &= ~0x800;
            return result;
        case 11:
            // Action 12: Set aiming flag
            playerData->flags |= 0x800;
            return result;
        case 12:
            // Action 13: Set shooting flag (bit3)
            playerData->flags |= 8;
            return result;
        case 13:
            // Action 14: Clear shooting flag
            playerData->flags &= ~8;
            return result;
        case 14:
            // Action 15: Clear reload flag (bit12)
            playerData->flags &= ~0x1000;
            return result;
        case 15:
            // Action 16: Set reload flag
            playerData->flags |= 0x1000;
            return result;
        case 16:
            // Action 17: Equip weapon (1 = equip)
            result = WeaponManager::toggleWeapon(1);  // FUN_006b50b0
            return result;
        case 17:
            // Action 18: Unequip weapon (0 = unequip)
            result = WeaponManager::toggleWeapon(0);
            return result;
        case 18:
            // Action 19: Enter/exit vehicle
            // +0x16c: vehicle state (1 = already in vehicle)
            if (playerData->inVehicle != 1) {
                result = VehicleController::enterVehicle();  // FUN_006b5a30
                return result;
            }
            VehicleController::exitVehicle(0, 0);  // FUN_006b4e30
            return 1;
        case 19:
            // Action 20: Start sprinting
            result = PlayerMovement::setSprintState(1);  // FUN_006b5d70
            return result;
        case 20:
            // Action 21: Stop sprinting
            result = PlayerMovement::setSprintState(0);
            // Note: fall-through? Actually the switch ends, returns result below
        }
    }
    return result;
}