// FUNC_NAME: PlayerSM::handleAction
undefined1 __thiscall PlayerSM::handleAction(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int actionId, undefined4 param_6)
{
    uint *puVar1;
    int *piVar2;
    char cVar3;
    undefined1 uVar4;
    undefined4 uVar5;
    int iVar6;
    undefined1 local_9;
    int local_8;
    uint local_4;

    local_9 = 1;
    local_4 = local_4 & 0xffffff00;
    local_8 = 0;
    FUN_007ba420(&local_8, &local_4); // get some state info
    if (*(char *)(this + 0x198) != (char)local_4) {
        // Reset some flags in the game manager when state changes
        *(undefined4 *)(*(int *)(this + 0x58) + 0x306c) = 0;
        *(undefined4 *)(*(int *)(this + 0x58) + 0x3070) = 0;
        *(undefined4 *)(*(int *)(this + 0x58) + 0x3074) = 0;
        *(undefined4 *)(*(int *)(this + 0x58) + 0x3078) = 0;
        *(undefined4 *)(*(int *)(this + 0x58) + 0x307c) = 0;
        *(char *)(this + 0x198) = (char)local_4;
    }
    switch(actionId + -0x32) {
    case 0: // Action 0x32
        uVar4 = FUN_006252f0(); // random or some value
        *(undefined1 *)(this + 0x74) = uVar4;
        *(undefined1 *)(*(int *)(this + 0x58) + 0x1ec4) = uVar4;
        return 1;
    case 1: // Action 0x33
        iVar6 = FUN_006252f0();
        piVar2 = (int *)(*(int *)(this + 0x58) + 0x306c + iVar6 * 4);
        *piVar2 = *piVar2 + 1;
        return 1;
    case 2: // Action 0x34
        uVar5 = FUN_006252f0();
        *(undefined4 *)(*(int *)(this + 0x58) + 0x3094) = uVar5;
        return 1;
    case 3: // Action 0x35
        FUN_007ab540(); // some setup
        FUN_007bb860(0, local_4, local_8); // play animation/sound
        return 1;
    case 4: // Action 0x36
        FUN_007ab540();
        FUN_007bb860(1, local_4, local_8);
        return 1;
    case 5: // Action 0x37
        uVar5 = FUN_006252f0();
        FUN_007b9d30(param_2, uVar5, local_8); // some action with parameter
        return 1;
    case 6: // Action 0x38
        iVar6 = FUN_006252f0();
        FUN_007f6420(0xe); // enable something
        if (iVar6 != 4) {
            FUN_007f63e0(0x37); // disable something
            if ((*(byte *)(this + 0x90) >> 1 & 1) != 0) {
                FUN_007f63e0(0x38); // disable another
                *(ushort *)(this + 0x90) = *(ushort *)(this + 0x90) & 0xfffd;
            }
            FUN_007ab730(); // some update
            return 1;
        }
        FUN_007f63e0(0x39);
        FUN_007ab730();
        return 1;
    case 7: // Action 0x39
        uVar5 = FUN_006252f0();
        FUN_00799510(param_2, uVar5); // some action
        FUN_007f6420(0x39);
        FUN_007f6420(0x37);
        FUN_007f6420(0x38);
        return 1;
    case 8: // Action 0x3A
        FUN_007ba6a0(param_2, param_3); // some action with two params
        return 1;
    case 9: // Action 0x3B
        uVar5 = FUN_00798f50(0x38); // get some object
        cVar3 = FUN_0079e920(uVar5); // check condition
        if (cVar3 != '\0') {
            *(ushort *)(this + 0x90) = *(ushort *)(this + 0x90) | 4;
            return 1;
        }
        break;
    case 10: // Action 0x3C
        uVar5 = FUN_00798f50(0x39);
        cVar3 = FUN_0079e920(uVar5);
        if (cVar3 != '\0') {
            *(ushort *)(this + 0x90) = *(ushort *)(this + 0x90) | 8;
            return 1;
        }
        break;
    case 0xb: // Action 0x3D
        if (((local_8 == 0) && (*(int *)(this + 0x188) != 0)) && (*(int *)(this + 0x188) != 0x48))
        {
            if (*(int *)(this + 0x188) == 0) {
                iVar6 = 0;
            }
            else {
                iVar6 = *(int *)(this + 0x188) + -0x48;
            }
            iVar6 = FUN_006bc8d0(iVar6, 0x369ac561); // hash lookup
            if ((iVar6 != 0) && ((char)local_4 == '\0')) {
                *(uint *)(iVar6 + 0x1f5c) = *(uint *)(iVar6 + 0x1f5c) | 0x800;
                return 1;
            }
        }
        break;
    case 0xc: // Action 0x3E
        if (((local_8 == 0) && (*(int *)(this + 0x188) != 0)) && (*(int *)(this + 0x188) != 0x48))
        {
            if (*(int *)(this + 0x188) == 0) {
                iVar6 = 0;
            }
            else {
                iVar6 = *(int *)(this + 0x188) + -0x48;
            }
            iVar6 = FUN_006bc8d0(iVar6, 0x369ac561);
            if (iVar6 != 0) {
                *(uint *)(iVar6 + 0x1f5c) = *(uint *)(iVar6 + 0x1f5c) | 0x1000;
                return 1;
            }
        }
        break;
    case 0xd: // Action 0x3F
        if (((local_8 == 0) && (*(int *)(this + 0x188) != 0)) && (*(int *)(this + 0x188) != 0x48))
        {
            if (*(int *)(this + 0x188) == 0) {
                iVar6 = 0;
            }
            else {
                iVar6 = *(int *)(this + 0x188) + -0x48;
            }
            iVar6 = FUN_006bc8d0(iVar6, 0x369ac561);
            if ((iVar6 != 0) && ((char)local_4 == '\0')) {
                *(uint *)(iVar6 + 0x1f5c) = *(uint *)(iVar6 + 0x1f5c) | 0x20000;
                return 1;
            }
        }
        break;
    case 0xe: // Action 0x40
        if ((*(int *)(this + 0x188) != 0) && (*(int *)(this + 0x188) != 0x48)) {
            if (*(int *)(this + 0x188) == 0) {
                iVar6 = 0;
            }
            else {
                iVar6 = *(int *)(this + 0x188) + -0x48;
            }
            iVar6 = FUN_006bc8d0(iVar6, 0x369ac561);
            if (iVar6 != 0) {
                *(uint *)(iVar6 + 0x1f5c) = *(uint *)(iVar6 + 0x1f5c) & 0xfffde7ff;
                return 1;
            }
        }
        break;
    case 0xf: // Action 0x41
        puVar1 = (uint *)(*(int *)(this + 0x58) + 0x24a0);
        *puVar1 = *puVar1 | 0x40000000;
        return 1;
    case 0x10: // Action 0x42
        if ((*(int *)(this + 0x188) != 0) && (*(int *)(this + 0x188) != 0x48)) {
            if (*(int *)(this + 0x188) == 0) {
                iVar6 = 0;
            }
            else {
                iVar6 = *(int *)(this + 0x188) + -0x48;
            }
            iVar6 = FUN_006bc8d0(iVar6, 0x369ac561);
            if (iVar6 != 0) {
                FUN_00747b80(); // some function
                return 1;
            }
        }
        break;
    default:
        local_9 = FUN_007abec0(param_2, param_3, param_4, actionId, param_6);
    }
    return local_9;
}