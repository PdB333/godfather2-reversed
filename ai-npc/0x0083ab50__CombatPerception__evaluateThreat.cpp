// FUNC_NAME: CombatPerception::evaluateThreat
int CombatPerception::evaluateThreat(void* this, void* target, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6, undefined4 param7, undefined4 param8)
{
    char cVar1;
    int iVar2;
    uint uVar3;
    int local_8;
    uint* local_4;

    uVar3 = 0;
    iVar2 = 3; // default: invalid/threat unknown

    // Check if this and target are valid, and target is active (offset +0x14)
    if ((this != 0) && (*(char*)((int)target + 0x14) != '\0')) {
        // Call inner function to evaluate something (e.g., distance, line-of-sight)
        iVar2 = FUN_0083bca0(this, target, param3, param4, param5, param6, param7, param8);
        if (iVar2 != 3) {
            local_8 = 0;
            local_4 = (uint*)0x0;
            // Look up a property by hash (0x998cab76) – likely "hasWeapon" or "isArmed"
            cVar1 = FUN_005fd340(*(short*)((int)target + 0x12), 0x998cab76, &local_8);
            if ((cVar1 != '\0') && (local_4 != (uint*)0x0) &&
                (local_8 != 0 && (*(char*)(local_8 + 6) == '\x02'))) {
                uVar3 = *local_4;
            }
            // If the property flag (bit 2) is set, return 1 (higher threat), else 2 (lower threat)
            iVar2 = 2 - (uint)((uVar3 & 4) != 0);
        }
    }
    return iVar2;
}