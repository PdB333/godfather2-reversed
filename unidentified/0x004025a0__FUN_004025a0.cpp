uint __thiscall FUN_004025a0(int param_1, uint param_2)
{
    uint* entry = *reinterpret_cast<uint**>(
        *reinterpret_cast<int*>(param_1 + 0x50) +
        (param_2 % *reinterpret_cast<uint*>(param_1 + 0x54)) * 4
    );

    while (true) {
        if (entry == nullptr) {
            return 0;
        }

        if (*entry == param_2) {
            break;
        }

        entry = reinterpret_cast<uint*>(entry[2]);
    }

    if (entry == nullptr) {
        return 0;
    }

    return entry[1];
}