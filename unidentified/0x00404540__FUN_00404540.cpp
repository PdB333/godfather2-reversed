int __thiscall FUN_00404540(undefined4 param_1, int param_2, undefined4 param_3)
{
    int resolved;

    if (param_2 == 0) {
        resolved = FUN_00405900(param_1, param_3);
    } else {
        resolved = FUN_004059b0(param_2);
    }

    if (resolved != 0) {
        const int object = FUN_004025a0(resolved);
        if ((*reinterpret_cast<int*>(object + 0x24) == 2) ||
            (*reinterpret_cast<int*>(object + 0x24) == 4)) {
            return 0;
        }
    }

    return resolved;
}