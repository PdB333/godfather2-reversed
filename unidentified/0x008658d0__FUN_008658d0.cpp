// FUNC_NAME: someClass::getWeightedDistanceOrSomething
float __thiscall FUN_008658d0(int param_1, int param_2, int param_3, float param_4)
{
    int *piVar1;
    int *piVar2;
    int iVar3;
    int iVar4;
    char cVar5;
    float fVar6;
    int local_8;
    float *local_4;

    // Check for special sentinel values (likely representing "no value" or "default")
    if ((param_4 == 1.4013e-45) ||
        ((fVar6 = DAT_00d756f0, param_4 != 2.8026e-45 && (fVar6 = DAT_00d756f4, param_4 != 4.2039e-45))
        )) {
        fVar6 = DAT_00d756ec;
    }
    // Access an array of pointers at offset +0x70 in param_3, indexed by param_1
    piVar1 = (int *)(param_3 + 0x70 + param_1 * 0xc);
    iVar3 = *piVar1;
    local_8 = 0;
    local_4 = (float *)0x0;
    param_4 = fVar6;
    if (iVar3 != 0) {
        // Access the same array at offset +0x70, indexed by param_2
        piVar2 = (int *)(param_3 + 0x70 + param_2 * 0xc);
        iVar4 = *piVar2;
        if ((((iVar4 != 0) &&
             (cVar5 = FUN_00862820(iVar3, piVar1[2], iVar4, piVar2[2], &DAT_00d756d4, &local_8),
             cVar5 != '\0')) && (local_4 != (float *)0x0)) &&
            (((local_8 != 0 && (*(char *)(local_8 + 6) == '\x03')) && (_DAT_00d577a0 < *local_4)))) {
            param_4 = *local_4;
        }
    }
    return (float10)param_4;
}