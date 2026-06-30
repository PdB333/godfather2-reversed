int FUN_00404590(uint param_1, int param_2, undefined4 param_3, float param_4, uint param_5)
{
    int* piVar1;
    byte bVar2;
    int in_EAX;
    int iVar3;
    int iVar4;
    undefined4* puVar5;
    undefined4* puVar6;
    undefined1* puVar7;
    undefined4 uVar8;
    int iVar9;
    uint uVar10;
    float fVar11;

    iVar9 = static_cast<int>(param_1);

    if (param_2 == 0) {
        iVar3 = FUN_00405900(param_3, 0);
    } else {
        iVar3 = FUN_004059b0(param_2);
    }

    if (iVar3 != 0) {
        iVar4 = FUN_004025a0(iVar3);
        if ((*reinterpret_cast<int*>(iVar4 + 0x24) == 2) ||
            (*reinterpret_cast<int*>(iVar4 + 0x24) == 4)) {
            iVar3 = 0;
        }

        if (iVar3 != 0) {
            if ((param_5 & 8) != 0) {
                iVar9 = FUN_004025a0(iVar3);
                if (iVar9 == 0) {
                    fVar11 = 0.0f;
                } else {
                    fVar11 = *reinterpret_cast<float*>(iVar9 + 0x48);
                }

                if (param_4 < fVar11) {
                    param_4 = fVar11;
                }
            }

            FUN_004042e0(iVar3, param_4);

            if ((param_5 & 0x10) == 0) {
                iVar9 = FUN_004025a0(iVar3);
                *reinterpret_cast<uint*>(iVar9 + 0x50) =
                    *reinterpret_cast<uint*>(iVar9 + 0x50) | 0x20;
            }

            return iVar3;
        }
    }

    iVar3 = FUN_00405720(param_2, 0);
    if (iVar3 != 0) {
        bVar2 = *reinterpret_cast<byte*>(iVar3 + 10);
        if ((bVar2 & 8) == 0) {
            if ((bVar2 & 0x10) == 0) {
                bVar2 = static_cast<byte>(~(bVar2 >> 2)) & 1;
            } else {
                bVar2 = 0;
            }
        } else {
            bVar2 = 1;
        }

        if (bVar2 == 0) {
            return 0;
        }
    }

    *reinterpret_cast<int*>(param_1 + 0x3c) =
        *reinterpret_cast<int*>(param_1 + 0x3c) + 1;
    uVar10 = *reinterpret_cast<uint*>(param_1 + 0x3c);

    param_1 = ((param_1 & 0xFFFFFF00u) | ((param_5 >> 2) & 0xFFu)) & 0xFFFFFF01u;

    puVar5 = reinterpret_cast<undefined4*>(FUN_00402840());
    if (in_EAX != 0) {
        puVar5[6] = in_EAX;
        iVar3 = FUN_004057f0(in_EAX);
        *reinterpret_cast<short*>(iVar3 + 0xe) =
            *reinterpret_cast<short*>(iVar3 + 0xe) + 1;

        if ((*reinterpret_cast<byte*>(in_EAX + 10) & 0x20) != 0) {
            puVar5[0x14] =
                puVar5[0x14] | (*reinterpret_cast<uint*>(in_EAX + 0xc) & 0xf) | 0x10;
        }
    }

    if (static_cast<char>(param_1) == '\0') {
        FUN_00402e90(puVar5 + 2, param_3, (uint)puVar5[0x14] >> 4 & 0xFFFFFF01u);
    } else {
        FUN_00402b40(puVar5);
    }

    puVar5[0xb] = param_2;
    puVar5[0x12] = param_4;
    puVar5[7] = uVar10;

    if ((param_5 & 0x10) == 0) {
        puVar5[0x14] = puVar5[0x14] | 0x20;
    }

    piVar1 = reinterpret_cast<int*>(iVar9 + 0x50);
    uVar10 = uVar10 % *reinterpret_cast<uint*>(iVar9 + 0x54);

    if ((*reinterpret_cast<char*>(iVar9 + 100) != '\0') &&
        (*reinterpret_cast<uint*>(iVar9 + 0x54) * 2 <=
         *reinterpret_cast<uint*>(iVar9 + 0x5c))) {
        FUN_00406dd0(piVar1);
        uVar10 = (uint)puVar5[7] % *reinterpret_cast<uint*>(iVar9 + 0x54);
    }

    puVar6 = reinterpret_cast<undefined4*>(FUN_00406d70());
    puVar6[1] = puVar5;
    *puVar6 = puVar5[7];
    puVar6[2] = *reinterpret_cast<undefined4*>(*piVar1 + uVar10 * 4);
    *reinterpret_cast<undefined4**>(*piVar1 + uVar10 * 4) = puVar6;

    puVar5[9] = 0;
    *puVar5 = 0;
    puVar5[1] = *reinterpret_cast<undefined4*>(iVar9 + 0x74);

    if (*reinterpret_cast<undefined4**>(iVar9 + 0x74) == nullptr) {
        *reinterpret_cast<undefined4**>(iVar9 + 0x70) = puVar5;
    } else {
        **reinterpret_cast<undefined4***>(iVar9 + 0x74) = puVar5;
    }

    *reinterpret_cast<undefined4**>(iVar9 + 0x74) = puVar5;

    puVar7 = reinterpret_cast<undefined1*>(puVar5[2]);
    if (puVar7 == nullptr) {
        puVar7 = &DAT_0120546e;
    }

    uVar8 = FUN_004d0740(puVar7, puVar5[0x12], param_1);
    puVar5[10] = uVar8;

    iVar9 = puVar5[7];
    FUN_004055f0();
    return iVar9;
}