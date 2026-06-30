// FUNC_NAME: Player::canEnterVehicle
bool __fastcall Player::canEnterVehicle(int thisPtr)
{
    bool result = false;
    int vehiclePtr = *(int *)(thisPtr + 0x16c); // +0x16c: currentVehiclePtr or vehicleHandle
    int flags = *(int *)(thisPtr + 0x34);       // +0x34: player state flags
    int animState = *(int *)(thisPtr + 0x40);   // +0x40: animation state machine ptr

    // Check player is not dead/downed (0x120000 = death/downed flags) and not stunned (bit 0)
    if ((((flags & 0x120000) == 0) && ((flags & 1) == 0)) && (animState != 0))
    {
        int animStateMachine = FUN_008c74d0(animState); // get animation state machine data
        if (((animStateMachine != 0) && 
             // Check anim state machine is not in ragdoll state (bit 5 of state flags)
             ((~(byte)(*(uint *)(animStateMachine + 0x84) >> 5) & 1) != 0)) &&
            // Not already in a vehicle
            ((vehiclePtr == 0 && ((flags >> 0x1c & 1) == 0))) &&
            // Check movement state: must be walking (1) or idle (0), or sprinting (bit 10 set)
            (((*(int *)(thisPtr + 0xc4) == 1) || (*(int *)(thisPtr + 0xc4) == 0)) || 
             ((flags >> 10 & 1) != 0))))
        {
            result = true;
        }
    }
    return result;
}