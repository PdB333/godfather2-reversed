// FUNC_NAME: SimEntity::checkActionTimeThreshold
uint SimEntity::checkActionTimeThreshold(int param_1, int param_2, uint param_3) {
    uint uVar1;
    float fVar2;
    char cVar3;
    int iVar4;
    int iVar5;
    uint3 uVar6;
    undefined4 local_4;

    if (*(int*)(param_1 + 4) == 0) {
        iVar4 = 0;
    } else {
        iVar4 = *(int*)(param_1 + 4) - 0x48; // Navigate to base component
    }
    iVar4 = *(int*)(iVar4 + 0x200c); // Get slot array pointer
    uVar6 = (uint3)((uint)iVar4 >> 8);
    if (iVar4 == 0) {
        return (uint)uVar6 << 8;
    }
    if (iVar4 == 0x3c) {
        return (uint)uVar6 << 8;
    }
    local_4 = *(float*)(iVar4 + 8); // Default cost multiplier

    // Same navigation for second check
    if (*(int*)(param_1 + 4) == 0) {
        iVar5 = 0;
    } else {
        iVar5 = *(int*)(param_1 + 4) - 0x48;
    }
    if (*(int*)(iVar5 + 0x200c) == 0) {
        iVar5 = 0;
    } else {
        iVar5 = *(int*)(iVar5 + 0x200c) - 0x3c;
    }
    if (*(int*)(iVar5 + 0x50) - 1 < 5) { // State check (e.g., action category < 5)
        cVar3 = FUN_0071f750(param_2);
        if (cVar3 != '\0') {
            local_4 = *(float*)(iVar4 + 0xc); // Override with alternate cost
        }
    }

    fVar2 = (float)(int)param_3; // Convert parameter to float (time/distance)
    if ((int)param_3 < 0) {
        fVar2 = fVar2 + DAT_00e44578; // Handle negative conversion (compiler idiom)
    }

    if ((param_2 != 0) && (uVar1 = *(uint*)(param_2 + 0x1ed8), param_3 = uVar1, uVar1 != 0) && (param_3 = uVar1 - 0x48, param_3 != 0)) {
        uVar6 = (uint3)(param_3 >> 8);
        if (fVar2 * local_4 <= *(float*)(uVar1 + 0xb8)) { // Check if scaled value <= threshold
            return CONCAT31(uVar6, 1); // Return handle with success flag
        }
        return (uint)uVar6 << 8; // Return handle with failure flag
    }
    return param_3 & 0xffffff00; // Return cleared lower byte if no valid handle
}