extern "C" void __thiscall FUN_00aa2680(int param_1, int param_2, undefined4 param_3)
{
    int* piVar1;
    undefined4* puVar2;
    int iVar3;

    if (0x2000 < param_2) {
        (**(code **)(**(int **)(param_1 + 0x10) + 0xc))(param_2, param_3);
        return;
    }

    if (param_2 < 0x201) {
        iVar3 = static_cast<int>(*reinterpret_cast<signed char*>(param_1 + 0x104 + param_2));
    } else {
        iVar3 = *reinterpret_cast<int*>(param_1 + 0x308 + (((param_2 - 1) >> 10) * 4));
    }

    puVar2 = *reinterpret_cast<undefined4**>(param_1 + 0x38 + iVar3 * 8);
    if (puVar2 != nullptr) {
        piVar1 = reinterpret_cast<int*>(param_1 + 0x3c + iVar3 * 8);
        *piVar1 = *piVar1 + -1;
        *reinterpret_cast<undefined4*>(param_1 + 0x38 + iVar3 * 8) = *puVar2;
        return;
    }

    FUN_00aa2150();
    return;
}