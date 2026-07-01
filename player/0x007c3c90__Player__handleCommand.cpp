// FUNC_NAME: Player::handleCommand
// Address: 0x007c3c90
// Role: Processes action codes (0x31–0x35) from the player input system.
// Checks player state, interacts with components, plays sounds, and updates selection.

bool Player::handleCommand(int arg1, int arg2, int arg3, int actionCode, int arg5)
{
    char cVar1;
    bool retVal = true;

    switch (actionCode) {
    case 0x31: // Accelerate / move action?
    {
        int playerHandle = getPlayerController(); // FUN_007ab6f0
        if ((playerHandle != 0) && 
            (cVar1 = isPlayerAlive(), cVar1 != '\0') && // FUN_00481620
            (cVar1 = isPlayerInVehicle(), cVar1 == '\0')) // FUN_00481660 -> not in vehicle
        {
            playSoundEffect(0x14); // FUN_007f63e0
            int component = getComponentFromHandle(playerHandle); // FUN_006bea40
            if (component != 0) {
                int vtable = *(int*)component;
                float speed = (float)(*(code *)(vtable + 0x2c))(component); // getSpeed
                (*(code *)(vtable + 0x3c))(component, speed); // setSpeed(speed)
            }
            return 1;
        }
        break;
    }
    case 0x32: // Interact / target change
    {
        cVar1 = isPlayerInVehicle(); // FUN_00481660
        if ((cVar1 != '\0') || (cVar1 = isPlayerOnFoot(), cVar1 != '\0')) // FUN_00481640
        {
            // Show interaction cue
            (*(code *)(*(int*)this + 0x2c))(0x3fcad2f5, 1, 1, 0, DAT_00e445ac, 0x3f800000);
        }

        int playerHandle = getPlayerController(); // FUN_007ab6f0
        if ((playerHandle != 0) && 
            (cVar1 = isPlayerOnFoot(), cVar1 != '\0')) // FUN_00481640
        {
            resetInteractionState(); // FUN_00801fd0
            int entity = findEntityByHash(playerHandle, 0x383225a1); // FUN_006c9470
            if (entity != 0) {
                int component = getComponentFromHandle(entity); // FUN_006bea40
                int vtable = *(int*)component;
                int statePtr = (*(code *)(vtable + 0x34))(component); // getCurrentState
                int targetIndex = 0;
                if (*(int*)(statePtr + 0xc) != 0) {
                    targetIndex = *(int*)(statePtr + 0xc) - 0x48; // offset for target list
                }
                if (targetIndex != this->currentTargetField) { // +0x58 (param_1[0x16])
                    setCurrentInteractionTarget(this->currentTargetField, playerHandle); // FUN_008a69e0
                    return 1;
                }
            }
        }
        break;
    }
    case 0x33: // Confirm selection
    {
        (*(code *)(*(int*)this + 0x2c))(0x726be970, 1, 1, 0, DAT_00e445ac, 0x3f800000);
        return 1;
    }
    case 0x34: // Cancel / back
    {
        (*(code *)(*(int*)this + 0x2c))(0x3fcad2f5, 1, 1, 0, DAT_00e445ac, 0x3f800000);
        return 1;
    }
    case 0x35: // Toggle something (e.g., minimap)
    {
        cVar1 = isPlayerInVehicle(); // FUN_00481660
        if ((cVar1 == '\0') && (cVar1 = isPlayerOnFoot(), cVar1 == '\0')) // FUN_00481640
        {
            (*(code *)(*(int*)this + 0x2c))(0xff13cee3, 1, 1, 0, 0x3f800000, 0x3f800000);
            return 1;
        }
        (*(code *)(*(int*)this + 0x2c))(0xd1e3aa2e, 1, 1, 0, DAT_00e445ac, 0x3f800000);
        cVar1 = isPlayerInVehicle(); // FUN_00481660
        if (cVar1 != '\0') {
            setMenuVisibility(0); // FUN_00472130
            return 1;
        }
        break;
    }
    default:
        retVal = handleCommandDefault(arg1, arg2, arg3, actionCode, arg5); // FUN_007abec0
    }

    return retVal;
}