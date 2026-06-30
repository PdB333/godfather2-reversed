// FUNC_NAME: PlayerController::canInitiateCombatAction
bool __thiscall PlayerController::canInitiateCombatAction(int this)
{
    int *nodePtr;
    char result;
    int weaponObj;
    int adjustedWeapon;
    int localCheck;

    // Check if player is in a state that prevents actions (e.g., cutscene, paused)
    // offset +0x18: pointer to some game state manager, +0x8e8: bitfield flag bit 6
    if ((*(uint *)(*(int *)(this + 0x18) + 0x8e8) >> 6 & 1) == 0) {
        // Get current weapon object pointer from manager (+0x24c4)
        weaponObj = *(int *)(*(int *)(this + 0x18) + 0x24c4);
        if (weaponObj == 0) {
            adjustedWeapon = 0;
        }
        else {
            adjustedWeapon = weaponObj + -0x48; // offset to real weapon data?
        }

        localCheck = this;
        // Check if current weapon is valid and ready
        if ((((adjustedWeapon == 0) ||
              (adjustedWeapon = FUN_0071ce70(adjustedWeapon), adjustedWeapon == 0)) ||
             ((*(ushort *)(adjustedWeapon + 0x3c) >> 0xb & 1) != 0)) ||
            (result = FUN_00718d40(adjustedWeapon + 0x10), result == '\0')) {
            // Current weapon not usable, check all weapons in inventory
            // +0x9c: linked list head of weapon nodes (first dword = weapon data, second dword = next pointer)
            result = FUN_0071ceb0();
            if (result != '\0') {
                for (nodePtr = *(int **)(this + 0x9c); nodePtr != (int *)0x0; nodePtr = (int *)nodePtr[1]) {
                    if ((*(ushort *)(*nodePtr + 0x3c) >> 0xb & 1) == 0) {
                        return 1; // Found a ready weapon
                    }
                }
            }
            // No ready weapon, try to auto-switch via FUN_00719810
            localCheck = 0;
            return FUN_00719810(&localCheck);
        }
    }
    return 1; // Action allowed (or blocked by state? Actually returns 1 as default)
}