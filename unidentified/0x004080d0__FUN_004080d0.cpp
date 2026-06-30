extern "C" int* __thiscall FUN_004080d0(int* param_1, int* param_2)
{
    const int value = *param_2;
    *param_1 = value;

    if (value != 0) {
        param_1 = FUN_00408030();
    }

    return param_1;
}