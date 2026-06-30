// FUNC_NAME: ActionManager::handleAction
undefined1 __thiscall ActionManager::handleAction(int *this, int actionArg, undefined4 param3, undefined4 param4, undefined4 actionId, undefined4 param6)
{
    char cVar1;
    undefined1 result;
    undefined4 uVar3;
    int iVar4;
    int ownerBase;
    int targetBase;
    int iVar6;
    int iVar7;
    float10 fVar8;
    undefined4 uVar9;
    undefined4 uVar10;
    undefined4 uVar11;
    undefined4 uVar12;

    result = 1;
    switch (actionId) {
        case 0x23: // Use Item / Activate Action
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(byte *)(ownerBase + 0x114) & 4) != 0) { // Check bit 2 of flags at +0x114
                    FUN_0073fe00(); // Generic function
                    ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                    iVar4 = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                    (**(code **)(*this + 0x2c)) // vtable[0x2c] (e.g., playAnimation)
                        (*(undefined4 *)(iVar4 + 0x98), 1, 0, *(int *)(ownerBase + 0x94) == 0, 0x3f800000, 0x3f800000);
                    this[0x21] = this[0x21] | 8; // Set flag 0x8
                    return 1;
                }
            }
            break;

        case 0x24: // Use Item (alternate)
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(byte *)(ownerBase + 0x114) & 4) != 0) {
                    ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                    if (*(int *)(ownerBase + 0x94) != 0) {
                        FUN_0073fe00();
                        ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                        (**(code **)(*this + 0x2c))(*(undefined4 *)(ownerBase + 0x94), 1, 0, 1, 0x3f800000, 0x3f800000);
                        this[0x21] = this[0x21] | 8;
                        return 1;
                    }
                }
            }
            break;

        case 0x25: // Use Offhand Item
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(byte *)(ownerBase + 0x114) & 4) != 0) {
                    ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                    if (*(int *)(ownerBase + 0x9c) != 0) {
                        FUN_0073fe00();
                        ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                        (**(code **)(*this + 0x2c))(*(undefined4 *)(ownerBase + 0x9c), 1, 1, 0, 0x3f800000, 0x3f800000);
                        this[0x21] = this[0x21] | 8;
                        return 1;
                    }
                }
            }
            break;

        case 0x26: // Drop / Place Item
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if (*(int *)(ownerBase + 0x90) != 0) {
                    ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                    uVar3 = *(undefined4 *)(ownerBase + 0x90);
                    uVar10 = 0;
                    uVar9 = FUN_006fbc40(0, 0); // Allocate / create
                    FUN_007f96a0(uVar3, 1, uVar9, uVar10); // Place/spawn at location
                    FUN_006fbc70(); // Finish allocation
                    return 1;
                }
            }
            break;

        case 0x27: // Start Aim / Shoot
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                FUN_007f63e0(0x60); // Play sound 0x60
                FUN_00726e40(this[0x17]); // Start animation on target?
                this[0x21] = this[0x21] & 0xfffffffe; // Clear bit 0
                this[0x22] = actionArg; // Store action argument
                return 1;
            }
            break;

        case 0x28: // Stop Aim / Shoot
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                FUN_007f6420(0x60); // Stop sound 0x60
                if (this[0x1c] != 0) {
                    FUN_00726ec0(this[0x17]); // Stop animation on target?
                    this[0x21] = this[0x21] | 1; // Set bit 0
                    return 1;
                }
                FUN_00726ec0(this[0x17]);
                this[0x21] = this[0x21] | 1;
                return 1;
            }
            break;

        case 0x29: // Melee Attack
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(byte *)(ownerBase + 0x114) & 4) == 0) {
                    iVar7 = *this;
                    uVar3 = FUN_007347e0(1, 0, 0, 0x3f800000, 0x3f800000); // Create melee hit object?
                    (**(code **)(iVar7 + 0x2c))(uVar3);
                    return 1;
                }
            }
            break;

        case 0x2a: // Spawn Projectile
            uVar12 = 0;
            uVar11 = 0;
            uVar10 = 0;
            uVar9 = 0;
            uVar3 = FUN_007347e0(0, 0, 0, 0); // Create projectile
            FUN_0045f020(uVar3, uVar9, uVar10, uVar11, uVar12); // Set position/velocity
            return 1;

        case 0x2b: // Pick Up / Equip
            if ((this[0x1e] != 0) && (this[0x1e] != 0x48)) {
                if (this[0x1e] != 0) {
                    FUN_0077de70(this[0x1e] + -0x48, this[0x17]); // Attach item to target?
                    return 1;
                }
                FUN_0077de70(0, this[0x17]);
                return 1;
            }
            break;

        case 0x2c: // Detach / Unequip
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                if (this[0x1c] != 0) {
                    FUN_0071e180(this[0x1c] + -0x48); // Detach owner
                    return 1;
                }
                FUN_0071e180(0);
                return 1;
            }
            break;

        case 0x2d: // Special Move / Ability
            iVar7 = this[0x12]; // Some pointer
            if (((uint)this[0x21] >> 1 & 1) == 0) {
                if (iVar7 != 0) {
                    (**(code **)(*(int *)(iVar7 + -0x48) + 0x168))(); // vtable[0x168]
                    return 1;
                }
                (**(code **)(iRam00000000 + 0x168))();
                return 1;
            }
            if (iVar7 != 0) {
                (**(code **)(*(int *)(iVar7 + -0x48) + 0x164))(); // vtable[0x164]
                return 1;
            }
            (**(code **)(iRam00000000 + 0x164))();
            return 1;

        case 0x2e: // Interact / Talk
            iVar7 = this[0x17]; // target
            iVar4 = this[0x1c]; // owner
            if (((((iVar4 != 0) && (iVar4 != 0x48)) && ((*(uint *)(iVar4 + 200) >> 0x13 & 1) != 0)) && // Check flag at owner+0xC8 (200)
                ((iVar7 != 0 && (cVar1 = FUN_0072d630(), cVar1 != '\0')))) &&
               (iVar4 = FUN_007326c0(), iVar4 != 0)) {
                iVar5 = FUN_00471610(); // Get player position?
                iVar6 = FUN_00471610(); // Get target position?
                fVar8 = (float10)FUN_0045c470(iVar6 + 0x30, iVar5 + 0x30); // Distance between
                if (fVar8 < (float10)_DAT_00e51568) { // Compare to global threshold
                    FUN_006f71b0(iVar7, iVar4); // Start interaction
                    return 1;
                }
            }
            break;

        case 0x2f: // Store Target Position
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(uint *)(ownerBase + 0x110) >> 0x15 & 1) != 0) { // Check flag at +0x110
                    iVar7 = FUN_00471610(); // Get position source
                    *(undefined8 *)(this + 0x23) = *(undefined8 *)(iVar7 + 0x30); // Copy XZ
                    this[0x25] = *(int *)(iVar7 + 0x38); // Copy Y
                    return 1;
                }
            }
            break;

        case 0x30: // Move to Stored Position
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(uint *)(ownerBase + 0x110) >> 0x15 & 1) != 0) {
                    (**(code **)(*(int *)this[0x17] + 0x1c))(this + 0x23); // Send position to target?
                    return 1;
                }
            }
            break;

        case 0x31: // AI Seek Target
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if ((*(uint *)(ownerBase + 0x110) >> 0x17 & 1) != 0) { // Check flag at +0x110
                    FUN_00624ca0(1); // Set flag
                    iVar7 = *this;
                    uVar3 = thunk_FUN_004dafd0("seekTargetTable"); // Get table by name
                    (**(code **)(iVar7 + 0x20))(actionArg, param3, uVar3); // vtable[0x20] set action table
                    return 1;
                }
            }
            break;

        case 0x32: // Taunt / Emote
            if ((this[0x1c] != 0) && (this[0x1c] != 0x48)) {
                ownerBase = (this[0x1c] == 0) ? 0 : (this[0x1c] + -0x48);
                if (((*(byte *)(ownerBase + 0x113) & 1) != 0) && (this[0x17] != 0)) {
                    FUN_007f63e0(0x69); // Play taunt sound
                    return 1;
                }
            }
            break;

        default:
            result = FUN_0073e610(actionArg, param3, param4, actionId, param6); // Defer to parent handler
    }
    return result;
}