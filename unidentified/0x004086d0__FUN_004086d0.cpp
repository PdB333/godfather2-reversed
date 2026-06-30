extern "C" void __thiscall FUN_004086d0(void* const param_1, int* const param_2)
{
    if ((*param_2 != 0) &&
        (static_cast<short>(param_2[1]) != 0))
    {
        const int iVar1 = FUN_00407da0();
        if (iVar1 != 0) {
            const int iVar2 = param_2[1];
            *reinterpret_cast<short*>(param_2 + 1) = static_cast<short>(iVar2) + -1;

            std::uint32_t uVar3 = static_cast<std::uint32_t>(*reinterpret_cast<std::uint16_t*>(iVar1 + 0x14));
            uVar3 = (((static_cast<int>(uVar3 * 2) >> 1) - 1U ^ uVar3) & 0x7fff) ^ uVar3;
            *reinterpret_cast<short*>(iVar1 + 0x14) = static_cast<short>(uVar3);

            if ((uVar3 & 0x7fff) == 0) {
                if (((*reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(param_1) + 4) >> 2) & 1) == 0) {
                    FUN_004095b0(*reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(param_1) + 8));
                } else if (((*reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(param_1) + 4) >> 3) & 1) == 0) {
                    FUN_00409730(*reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(param_1) + 8));
                } else {
                    FUN_004098a0(*reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(param_1) + 8));
                }

                const int iVar2_2 = FUN_00407c50();
                if ((*reinterpret_cast<std::uint8_t*>(iVar2_2 + 0x16) & 1) != 0) {
                    *reinterpret_cast<std::uint16_t*>(iVar1 + 0x14) =
                        *reinterpret_cast<std::uint16_t*>(iVar1 + 0x14) | 0x8000;
                    *reinterpret_cast<std::uint32_t*>(iVar1 + 0x0c) = 0;
                    *reinterpret_cast<std::uint32_t*>(iVar1 + 0x0c) =
                        *reinterpret_cast<std::uint32_t*>(iVar2_2 + 0x0c);
                    *reinterpret_cast<int*>(iVar2_2 + 0x0c) = iVar1;
                    return;
                }

                FUN_004091f0();
                FUN_00407ae0();
            }
        }
    }
}