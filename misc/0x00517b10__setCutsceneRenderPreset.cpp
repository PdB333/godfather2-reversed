// FUNC_NAME: setCutsceneRenderPreset

void setCutsceneRenderPreset(void)
{
    int localVar;
    uint uVar4;
    int iVar5;
    int iVar3;

    FUN_00609890(1); // some initialization
    iVar5 = DAT_012058a4;
    if (DAT_012054dc != 0) {
        iVar5 = *(int *)(DAT_012054dc + 0x16c); // dereference
    }
    _DAT_01205500 = _DAT_01205500 + 1;
    FUN_0052be20(_DAT_012192d8,
                 (&DAT_01218e50)[((-(uint)(DAT_012192f0 == 0x4000000) & 0xfffffff6) + 0x11) * 2],
                 DAT_012192f0 == 0x4000000);
    iVar3 = DAT_012058a4;
    if (DAT_012054dc != 0) {
        iVar3 = *(int *)(DAT_012054dc + 0x16c);
    }
    uVar4 = 0;
    do {
        if ((&DAT_01218e50)[uVar4 * 2] == iVar3) {
            if (uVar4 < 20) {
                (&DAT_01218e54)[uVar4 * 2] = (&DAT_01218e54)[uVar4 * 2] & 0xfffffffc;
            }
            break;
        }
        uVar4 = uVar4 + 1;
    } while (uVar4 < 20);
    uVar2 = DAT_011f38f4;
    uVar1 = DAT_011f38f0;
    DAT_011f38f4 = 0;
    DAT_011f38f0 = iVar3;
    FUN_00609340(0, uVar1, uVar2); // some matrix/transform call
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // set float constants (1.0,1.0)

    // Set min/max camera values for multiple presets
    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1;

    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 1;

    if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
    }
    if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
    }
    _DAT_011f3a3c = 7;

    if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
    }
    if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
    }
    _DAT_011f3a38 = 0;

    if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = 0;

    FUN_00417cf0(1, 5, 6); // some effect or animation

    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0;

    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 1;

    iVar3 = DAT_012058a4;
    if (DAT_012054dc != 0) {
        iVar3 = *(int *)(DAT_012054dc + 0x16c);
    }
    if (iVar5 == iVar3) {
        _DAT_01205500 = _DAT_01205500 - 1;
    }
    return;
}