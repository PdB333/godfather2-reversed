// FUNC_NAME: StreamManager::compactStreamSlots
void __fastcall StreamManager::compactStreamSlots(int this)
{
    int iVar1;
    uint uVar2;
    int iVar3;
    int *piVar4;
    uint uVar5;
    uint uVar6;
    undefined4 *puVar7;
    uint local_4;

    uVar2 = *(uint *)(this + 0x58); // +0x58: streamCount (number of active stream slots)
    if ((*(uint *)(this + 0x60) < uVar2) && (uVar6 = 0, uVar2 != 0)) {
        piVar4 = *(int **)(this + 0x54); // +0x54: streamSlots array (array of pairs: [type, data])
        while ((*piVar4 != 0 && (*piVar4 != 0x48))) {
            uVar6 = uVar6 + 1;
            piVar4 = piVar4 + 2;
            if (uVar2 <= uVar6) {
                return;
            }
        }
        if (uVar6 < uVar2) {
            uVar5 = uVar6 + 1;
            if (uVar5 < uVar2) {
                piVar4 = *(int **)(this + 0x54) + uVar5 * 2;
                do {
                    if ((*piVar4 != 0) && (*piVar4 != 0x48)) break;
                    uVar5 = uVar5 + 1;
                    piVar4 = piVar4 + 2;
                } while (uVar5 < uVar2);
            }
            local_4 = *(uint *)(this + 0x6c); // +0x6c: some count (maybe active stream count)
            if (uVar6 <= *(uint *)(this + 0x6c)) {
                local_4 = uVar6;
            }
            if (uVar5 < uVar2) {
                do {
                    iVar1 = uVar5 * 8;
                    iVar3 = *(int *)(iVar1 + *(int *)(this + 0x54));
                    if ((iVar3 != 0) && (iVar3 != 0x48)) {
                        if (uVar5 < *(uint *)(this + 0x6c)) {
                            local_4 = local_4 + 1;
                        }
                        FUN_00909080(iVar1 + *(int *)(this + 0x54)); // likely streamSlot::reset or close
                        puVar7 = (undefined4 *)(*(int *)(this + 0x54) + iVar1);
                        if (*(int *)(*(int *)(this + 0x54) + iVar1) != 0) {
                            FUN_004daf90(puVar7); // likely operator delete or release
                            *puVar7 = 0;
                        }
                        uVar6 = uVar6 + 1;
                    }
                    uVar5 = uVar5 + 1;
                } while (uVar5 < *(uint *)(this + 0x58));
            }
            FUN_00909c80(uVar6); // likely update some count or notify
            *(uint *)(this + 0x6c) = local_4; // +0x6c: update active count
        }
    }
    return;
}