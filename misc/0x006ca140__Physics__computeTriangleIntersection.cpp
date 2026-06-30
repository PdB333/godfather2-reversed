// FUNC_NAME: Physics::computeTriangleIntersection
undefined4 FUN_006ca140(undefined4 param_1, undefined4 param_2, float *param_3)
{
    int *piVar1;
    int iVar2;
    int iVar3;
    float *pfVar4;
    float fStack_320;
    float fStack_31c;
    float fStack_318;
    undefined4 uStack_314;
    int local_304;
    float local_300;
    float fStack_2fc;
    float fStack_2f8;
    float fStack_2f0;
    float fStack_2ec;
    float fStack_2e8;
    float fStack_2e0;
    float fStack_2dc;
    float fStack_2d8;
    undefined **local_2d0;
    undefined4 local_2cc;
    undefined4 local_2b0;
    undefined4 local_2ac;
    undefined4 local_2a0;
    undefined4 uStack_29c;
    undefined4 local_280;
    int *local_270;
    undefined1 local_260 [80];
    undefined1 auStack_210 [524];

    // Initialize collision query
    FUN_00542650(param_1, param_2, 2, 0x1000000, 0, 0);
    local_2ac = 0xffffffff;
    local_2a0 = 0xffffffff;
    local_2d0 = &PTR_FUN_00e32a8c;
    local_270 = (int *)0x0;
    local_2b0 = _DAT_00d5780c;
    local_280 = 0;
    local_2cc = _DAT_00d5780c;
    FUN_009e5ed0(local_260, &local_2d0);
    if (local_270 != (int *)0x0) {
        piVar1 = (int *)*local_270;
        iVar2 = piVar1[3];
        if (iVar2 == 0xb) {
            piVar1 = (int *)(**(code **)(*piVar1 + 0x14))();
            piVar1 = (int *)(**(code **)(*piVar1 + 0x14))(uStack_29c, auStack_210);
            iVar2 = piVar1[3];
        }
        if (iVar2 == 4) {
            local_304 = local_270[2];
            pfVar4 = &local_300;
            iVar2 = 0x20 - (int)pfVar4;
            iVar3 = 3;
            do {
                FUN_00aa2bb0(local_304, (int)piVar1 + iVar2 + (int)pfVar4);
                pfVar4 = pfVar4 + 4;
                iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            // Compute barycentric coordinates for triangle intersection
            fStack_320 = (fStack_2d8 - fStack_2f8) * (fStack_2ec - fStack_2fc) -
                         (fStack_2dc - fStack_2fc) * (fStack_2e8 - fStack_2f8);
            fStack_318 = (fStack_2dc - fStack_2fc) * (fStack_2f0 - local_300) -
                         (fStack_2e0 - local_300) * (fStack_2ec - fStack_2fc);
            fStack_31c = (fStack_2e0 - local_300) * (fStack_2e8 - fStack_2f8) -
                         (fStack_2d8 - fStack_2f8) * (fStack_2f0 - local_300);
            param_3[2] = fStack_318;
            *param_3 = fStack_320;
            param_3[1] = fStack_31c;
            uStack_314 = 0;
            FUN_0056afa0(&fStack_320, &fStack_320);
            *param_3 = fStack_320;
            param_3[1] = fStack_31c;
            param_3[2] = fStack_318;
        }
        return 1;
    }
    param_3[2] = 0.0;
    param_3[1] = 0.0;
    *param_3 = 0.0;
    return 0;
}