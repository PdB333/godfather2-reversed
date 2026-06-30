extern "C" void __fastcall FUN_00408900(std::uint32_t /*param_1*/, std::int32_t param_2, std::uint32_t param_3)
{
    *reinterpret_cast<std::int16_t*>(param_2 + 4) =
        *reinterpret_cast<std::int16_t*>(param_2 + 4) + 1;

    const auto iVar2 = FUN_00407da0();

    if (iVar2 != 0)
    {
        const auto uVar1 = *reinterpret_cast<std::uint16_t*>(iVar2 + 0x14);

        *reinterpret_cast<std::uint16_t*>(iVar2 + 0x14) =
            (((static_cast<std::int16_t>(static_cast<int>(static_cast<std::uint32_t>(uVar1) * 2) >> 1) + 1U) ^ uVar1) & 0x7fff) ^ uVar1;

        return;
    }

    FUN_004084d0(param_2, param_3);
}