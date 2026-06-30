// FUNC_NAME: SimNpc::evaluateCondition
bool SimNpc::evaluateCondition(int extraParam, uint paramA, int conditionId, int paramB)
{
    byte result = false;
    switch (conditionId - 10) {
    case 0: // conditionId == 10
        return FUN_007578c0(); // some condition check
    case 1: // conditionId == 11
        if ((*(uint *)(this + 0xa8) >> 0xc & 1) != 0) return false; // bit 12 of flags
        {
            int state = *(int *)(this + 0x130); // e.g., AI state
            int count = (**(code **)(**(int **)(this + 0x10c) + 8))(); // vtable call -> get count
            if (state != 3 && *(int *)(this + 0x14c) != count - 1) {
                int ptr = *(int *)(this + 0x100);
                if (ptr == 0) return false;
                if ((*(byte *)(ptr + 0xb4) & 1) == 0) return false;
                *(uint *)(ptr + 0xb4) &= 0xfffffffe; // clear bit 0
            }
            result = FUN_009a77c0(*(undefined4 *)(this + 0x58), this + 0x60);
        }
        goto finish;
    case 2: // conditionId == 12
        return *(int *)(this + 0x20) == 0;
    case 0x14: // conditionId == 30
        return (bool)FUN_007585d0(); // distance check?
    case 3: // conditionId == 13
        if ((*(uint *)(this + 0xa8) >> 0xc & 1) != 0) return false;
        {
            undefined1 local_c[12];
            FUN_0075d6e0(local_c, this + 0x60, paramA, &conditionId);
            int playerPos = FUN_00471610(); // get player position struct
            if (*(float *)(this + 100) - *(float *)(playerPos + 0x34) < *(float *)0x00d5780c) return false; // time threshold?
            if ((char)conditionId != 0) return false;
            result = FUN_009a77c0(*(undefined4 *)(this + 0x58), this + 0x60);
        }
        return (bool)result;
    case 4: // conditionId == 14
        break; // fall through to return true
    case 5: // conditionId == 15
        return *(int *)(this + 0x130) == 3;
    case 6: // conditionId == 16
        return (bool)FUN_00756f40();
    case 7: // conditionId == 17
        if (!FUN_00756f90()) return false;
        if (*(int **)(this + 0x10c) != (int *)0x0) {
            if ((**(code **)(**(int **)(this + 0x10c) + 8))() != 0) return false;
        }
        break;
    case 8: // conditionId == 18
        if (!FUN_00756f90()) return false;
        if (*(int **)(this + 0x10c) == (int *)0x0) return false;
        if ((**(code **)(**(int **)(this + 0x10c) + 8))() != 0) return false;
        if (!FUN_009a77c0(*(undefined4 *)(this + 0x58), this + 0x60)) return false;
        return true;
    case 9: // conditionId == 19
        if (*(int **)(this + 0x10c) == (int *)0x0) return false;
        {
            uint count = (**(code **)(**(int **)(this + 0x10c) + 8))();
            if (count > 1) {
                int count2 = (**(code **)(**(int **)(this + 0x10c) + 8))();
                if (*(int *)(this + 0x14c) != count2 - 1) return false;
            }
            result = FUN_009a77c0(*(undefined4 *)(this + 0x58), this + 0x60);
        }
        goto label_007590ad;
    case 10: // conditionId == 20
        return *(int *)(this + 0x20) == 0;
    case 0xb: // conditionId == 21
    {
        int local_24 = 0;
        paramB = 0;
        uint local_1c = *(uint *)(*(int *)(this + 0x100) + 0x114); // bitmask from some component
        uint count = (**(code **)(**(int **)(this + 0x10c) + 8))();
        uint uVar10 = *(uint *)(this + 0x14c);
        uint uStack_2c = uVar10;
        while (uStack_2c = uStack_2c + 1, uVar10 < count) {
            (**(code **)(**(int **)(this + 0x10c) + 0xc))(uVar10); // create iterator?
            char cVar = FUN_005f5cb0(&local_24, &paramB);
            result |= (cVar == 0);
            if (!result && !(*(ushort *)(paramB + 0x18) & 0xc000)) {
                if (uStack_2c >= count) continue;
                int iStack_20 = 0;
                paramA = 0;
                uint uVar7 = (**(code **)(**(int **)(this + 0x10c) + 0xc))(uStack_2c);
                cVar = FUN_005f5cb0(&iStack_20, &paramA);
                result = (cVar == 0);
                if (!result && FUN_005fd760(uVar7) != 0) {
                    uint uVar1 = paramA;
                    bool bVar9 = result || (*(ushort *)(paramA + 0x18) & 0xc000) != 0;
                    paramA &= 0xffffff00;
                    if (iStack_20 == local_24) {
                        int iVar5 = FUN_005f5ec0(paramB, uVar1);
                        if (iVar5 != 0) {
                            uVar1 = local_1c & *(ushort *)(iVar5 + 10);
                            goto LAB_00759527;
                        }
                    } else {
                        int iVar5 = FUN_005f5f20(paramB, uVar7);
                        if (iVar5 != 0) {
                            uVar1 = local_1c & *(ushort *)(iVar5 + 10);
LAB_00759527:
                            bVar9 |= (uVar1 != 0);
                            paramA = CONCAT31(paramA._1_3_, 1);
                        }
                    }
                    result = bVar9 | ((char)paramA == 0);
                }
            }
            uVar10++;
            if (result) return true;
        }
        goto finish;
    }
    case 0xc: // conditionId == 22
        if (*(int *)(this + 0x130) != 2) return false;
        if ((*(uint *)(this + 0xa8) >> 0x11 & 1) == 0) return false;
        return true;
    case 0xd: // conditionId == 23
        return *(float *)(this + 0x30) > *(float *)0x00d5780c;
    case 0xe: // conditionId == 24
        if ((*(uint *)(this + 0xa8) >> 0x17 & 1) == 0 && *(int *)(this + 0x130) != 2) return false;
        break;
    case 0xf: // conditionId == 25
        if ((*(uint *)(this + 0xa8) >> 0x12 & 1) == 0 && *(uint *)(this + 0x150) < 3) return false;
        break;
    case 0x10: // conditionId == 26
        return FUN_0054f460(*(void**)0x00d5ef88) == 0;
    case 0x11: // conditionId == 27
    {
        if (FUN_005fd740() == 0) break;
        if (FUN_005fd740() == 0) break;
        paramA = 0;
        return FUN_005f5cb0(&paramA, &conditionId) == 0;
    }
    case 0x12: // conditionId == 28
        return (*(byte *)(*(int *)(this + 0x58) + 0x1b97) & 1) != 0;
    case 0x13: // conditionId == 29
        if ((*(byte *)(*(int *)(this + 0x58) + 0x1b97) & 1) == 0) return false;
        result = *(byte *)(this + 0xa8) & 1;
label_007590ad:
        if (result == 0) return false;
        break;
    case 0x15: // conditionId == 31
        return (bool)FUN_0054f220(500);
    default:
        return (bool)FUN_004ac640(extraParam, paramA, conditionId, paramB);
    case 0x17: // conditionId == 33
    {
        if (!FUN_007585d0()) return false;
        float local_18, local_14, local_10;
        if (!FUN_00758570(&local_18)) return false;
        int playerPos = FUN_00471610();
        float dx = local_18 - *(float *)(playerPos + 0x30);
        float dy = local_14 - *(float *)(playerPos + 0x34);
        float dz = local_10 - *(float *)(playerPos + 0x38);
        float distSq = dx*dx + dy*dy + dz*dz;
        if (distSq < *(float *)0x00d651e4 * *(float *)0x00d651e4) return true;
        return false;
    }
    case 0x18: // conditionId == 34
        return (*(uint *)(this + 0xa8) >> 0x13 & 1) != 0;
    }
    return true;

finish:
    if (result == 0) return false;
    return true;
}