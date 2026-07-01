// FUNC_NAME: PlayerSM::canPerformAction
bool __thiscall PlayerSM::canPerformAction(int a2, int a3, unsigned int actionId, int a5)
{
    bool bResult;
    char cTemp;

    switch (actionId) {
    case 0x15: // e.g., ACTION_DODGE
        return FUN_008a4380(); // likely isPlayerRagdoll() or isDead()

    case 0x16: // e.g., ACTION_MELEE_ATTACK
        cTemp = FUN_00481660(); // isPlayerInCombat()?
        if (cTemp == 0 || (cTemp = FUN_007f47a0(), cTemp == 0)) {
            bResult = false;
        } else {
            bResult = true;
        }
        // Additional check: if player is in vehicle and vehicle-specific flag is clear, allow.
        cTemp = FUN_00481640(); // isPlayerInVehicle()
        if (cTemp != 0 && *(char *)(*(int *)(this + 0x58) + 0x2438) == 0) {
            return true;
        }
        break;

    case 0x17: // e.g., ACTION_ENTER_VEHICLE
        cTemp = FUN_00481620(); // isGamePaused()?
        if (cTemp == 0) return false;
        if (*(char *)(DAT_0112a838 + 0xcd) == 0) return false; // global vehicle availability
        return true;

    case 0x18: // e.g., ACTION_ENTER_COVER
        cTemp = FUN_00481620(); // isGamePaused()?
        if (cTemp != 0 && _DAT_00d6fb5c < *(float *)(this + 0x30)) {
            return true;
        }
        return false;

    default:
        bResult = FUN_007ab790(a2, a3, actionId, a5); // base class handler
    }
    return bResult;
}