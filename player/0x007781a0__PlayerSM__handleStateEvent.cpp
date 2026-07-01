// FUNC_NAME: PlayerSM::handleStateEvent
uint __thiscall PlayerSM::handleStateEvent(int this, float param_2, undefined4 param_3, undefined4 param_4, float param_5, undefined4 param_6)
{
    int *vtable;
    float fVar2;
    char cVar3;
    int iVar4;
    undefined4 uVar5;
    int *piVar6;
    float10 fVar7;
    float10 fVar8;
    float fVar9;
    undefined1 *puVar10;
    undefined4 uVar11;
    byte local_19;
    undefined4 local_18;
    undefined4 local_14;
    
    vtable = *(int **)(this + 0x5c); // +0x5c: vtable pointer
    local_19 = 1;
    switch(param_5) {
    case 4.90454e-44: // State ID 0x0A (10) - Enter state
        FUN_007f63e0(0x5a); // Audio: play sound 0x5A
    case 5.1848e-44: // State ID 0x0B (11)
    case 5.46506e-44: // State ID 0x0C (12)
        if ((param_5 == 4.90454e-44) && ((*(uint *)(this + 0xac) >> 7 & 1) == 0)) { // +0xac: flags
            *(uint *)(this + 0xac) = *(uint *)(this + 0xac) | 0x80; // Set bit 7
        }
        param_5 = _DAT_00d5c458; // Some global float
        if ((*(uint *)(this + 0xac) >> 10 & 1) != 0) { // Check bit 10
            param_5 = DAT_00e445f0; // Alternative global float
        }
        FUN_00777200(4); // Set state to 4
        fVar2 = (float)(int)param_2;
        if ((int)param_2 < 0) {
            fVar2 = fVar2 + DAT_00e44578; // Handle negative
        }
        *(float *)(this + 0xa4) = fVar2 * DAT_00d5efb8 + param_5; // +0xa4: some timer/position
        return 1;
    case 5.04467e-44: // State ID 0x0D (13)
    case 5.32493e-44: // State ID 0x0E (14)
    case 5.60519e-44: // State ID 0x0F (15)
        fVar2 = (float)(int)param_2;
        if ((int)param_2 < 0) {
            fVar2 = fVar2 + DAT_00e44578;
        }
        fVar9 = _DAT_00d5c458;
        if ((*(uint *)(this + 0xac) >> 10 & 1) != 0) {
            fVar9 = DAT_00e445f0;
        }
        if (*(float *)(this + 0xa4) <= fVar2 * DAT_00d5efb8) {
            param_2 = _DAT_00d5780c;
        }
        else {
            param_2 = _DAT_00d5780c - (*(float *)(this + 0xa4) - fVar2 * DAT_00d5efb8) / fVar9;
        }
        iVar4 = FUN_00875b90(this + 0x80); // Get some component at +0x80
        if (param_5 == 5.04467e-44) {
            *(float *)(iVar4 + 0x14) = param_2 * DAT_00d681a4; // Set blend weight
            return 1;
        }
        *(float *)(iVar4 + 0x14) = DAT_00d681a4 - param_2 * DAT_00d681a4; // Inverse blend
        return 1;
    case 5.74532e-44: // State ID 0x10 (16)
        FUN_00777200(5); // Set state to 5
        FUN_007f63e0(0x5a); // Play sound
        uVar11 = 0;
        uVar5 = FUN_006fbc40(0,0); // Get some object
        FUN_007f96a0(0x5393fcca,4,uVar5,uVar11); // Play animation
        FUN_006fbc70(); // Release object
        FUN_00777380(); // Some cleanup
        return 1;
    case 5.88545e-44: // State ID 0x11 (17)
        iVar4 = FUN_00800a90(); // Get player
        uVar5 = DAT_00d5ccf8;
        fVar2 = (float)(int)param_2;
        if ((int)param_2 < 0) {
            fVar2 = fVar2 + DAT_00e44578;
        }
        fVar2 = fVar2 * DAT_00d5efb8;
        *(undefined4 *)(this + 0x9c) = DAT_00d5ccf8; // +0x9c: some value
        fVar2 = fVar2 + _DAT_00d5c458;
        *(undefined4 *)(this + 0xa8) = uVar5; // +0xa8: another value
        *(float *)(this + 0xa0) = fVar2; // +0xa0: timer/position
        FUN_00776500(); // Some update
        if (iVar4 != 0) {
            if (*(char *)(iVar4 + 0x1aa) == '\x01') { // Check player flag
                FUN_00777200(0); // Set state to 0
                return 1;
            }
            FUN_00777200(1); // Set state to 1
            return 1;
        }
        break;
    case 6.02558e-44: // State ID 0x12 (18)
        iVar4 = FUN_00800a90();
        if (iVar4 == 0) {
            uVar5 = FUN_00777310(); // Get some object
            (**(code **)(*vtable + 600))(uVar5); // Call vtable method
        }
        FUN_00777c90(param_2,~(byte)(*(uint *)(this + 0xac) >> 1) & 1); // Some update with flag
        return 1;
    case 6.16571e-44: // State ID 0x13 (19)
        FUN_00778070(param_2); // Handle state
        return 1;
    case 6.30584e-44: // State ID 0x14 (20)
        iVar4 = FUN_00800a90();
        if (((iVar4 != 0) && (cVar3 = FUN_00701010(), cVar3 != '\0')) &&
           (cVar3 = FUN_00701280(), cVar3 != '\0')) {
            fVar2 = (float)(int)param_2;
            if ((int)param_2 < 0) {
                fVar2 = fVar2 + DAT_00e44578;
            }
            fVar2 = fVar2 * DAT_00d5efb8;
            fVar7 = (float10)FUN_00701020(); // Get some value
            if (fVar7 + (float10)*(float *)(this + 0x98) < (float10)fVar2) { // +0x98: accumulated time
                *(float *)(this + 0x98) = fVar2;
                (**(code **)(*vtable + 0x264))(); // Call vtable method
            }
        }
        FUN_00777c90(param_2,~(byte)(*(uint *)(this + 0xac) >> 1) & 1);
        return 1;
    case 6.44597e-44: // State ID 0x15 (21)
        iVar4 = FUN_00800a90();
        if (iVar4 != 0) {
            FUN_00701f40(); // Some action
            return 1;
        }
        break;
    case 6.5861e-44: // State ID 0x16 (22)
        FUN_00777200(6); // Set state to 6
        return 1;
    case 6.72623e-44: // State ID 0x17 (23)
        FUN_00777200(7); // Set state to 7
        return 1;
    case 6.86636e-44: // State ID 0x18 (24)
    case 7.00649e-44: // State ID 0x19 (25)
        FUN_00777200(6);
        if (((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) &&
           ((*(uint *)(this + 0xac) >> 0xb & 1) != 0)) { // Check bit 11
            *(uint *)(this + 0xac) = *(uint *)(this + 0xac) & 0xfffff7ff; // Clear bit 11
            if (*(int *)(this + 0x70) != 0) {
                FUN_007763e0(); // Some action
                return 1;
            }
            FUN_007763e0();
            return 1;
        }
        break;
    case 7.14662e-44: // State ID 0x1A (26)
        FUN_00776980(); // Handle state
        return 1;
    case 7.28675e-44: // State ID 0x1B (27)
        FUN_00777f10(); // Some setup
        iVar4 = FUN_00800a90();
        if (iVar4 != 0) {
            uVar5 = FUN_00701050(); // Get some value
            fVar7 = (float10)FUN_007159b0(uVar5); // Get another value
            fVar8 = (float10)(int)param_2;
            if ((int)param_2 < 0) {
                fVar8 = fVar8 + (float10)DAT_00e44578;
            }
            *(float *)(this + 0x94) = (float)(fVar8 * (float10)DAT_00d5efb8 + fVar7); // +0x94: some timer
            return 1;
        }
        break;
    case 7.42688e-44: // State ID 0x1C (28)
        FUN_007764d0(); // Handle state
        return 1;
    case 7.56701e-44: // State ID 0x1D (29)
        if ((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) {
            local_14 = 0;
            local_18 = 0;
            if (*(int *)(this + 0x70) == 0) {
                piVar6 = (int *)0x0;
            }
            else {
                piVar6 = (int *)(*(int *)(this + 0x70) + -0x48); // Get parent object
            }
            (**(code **)(*piVar6 + 0x1f8))(piVar1,&local_18); // Call parent method
            if (*(int *)(this + 0x70) == 0) {
                piVar6 = (int *)0x0;
            }
            else {
                piVar6 = (int *)(*(int *)(this + 0x70) + -0x48);
            }
            puVar10 = &stack0xffffffe0;
            uVar5 = (**(code **)(*piVar6 + 0x280))(); // Get some value
            (**(code **)(*vtable + 0x14c))(uVar5,1,0); // Call vtable method
            return (uint)puVar10 >> 0x18;
        }
        break;
    case 7.70714e-44: // State ID 0x1E (30)
        *(uint *)(this + 0xac) = *(uint *)(this + 0xac) & 0xffffff7f; // Clear bit 7
        FUN_007f6420(0x5a); // Stop sound
        return 1;
    case 7.84727e-44: // State ID 0x1F (31)
        if (*(int *)(this + 0x70) != 0) {
            FUN_00778b10(vtable,*(int *)(this + 0x70) + -0x48); // Some action with parent
            return 1;
        }
        FUN_00778b10(vtable,0);
        return 1;
    default:
        local_19 = FUN_0073e610(param_2,param_3,param_4,param_5,param_6); // Default handler
    }
    return (uint)local_19;
}