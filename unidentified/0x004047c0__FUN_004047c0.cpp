uint __thiscall FUN_004047c0(int param_1, int* param_2, float param_3)
{
    int* current = *reinterpret_cast<int**>(param_1 + 0x70);
    uint result = in_EAX & 0xffffff00;
    int index = 0;

    if (current != nullptr) {
        while (current != param_2) {
            current = reinterpret_cast<int*>(*current);
            index = index + 1;
            if (current == nullptr) {
                return result;
            }
        }

        if (-1 < index) {
            const float fVar1 = static_cast<float>(param_2[0x12]);
            undefined3 uVar3 = CONCAT21(
                static_cast<short>(in_EAX >> 0x10),
                static_cast<unsigned char>(
                    ((fVar1 == param_3) ? 1 : 0) << 6 |
                    ((std::isnan(fVar1) || std::isnan(param_3)) ? 1 : 0) << 2 |
                    2U |
                    ((fVar1 < param_3) ? 1 : 0)
                )
            );

            if (fVar1 != param_3) {
                param_2[0x12] = static_cast<int>(param_3);
                FUN_004d0ba0(param_3);
                uVar3 = extraout_var;
            }

            result = CONCAT31(uVar3, 1);
        }
    }

    return result;
}