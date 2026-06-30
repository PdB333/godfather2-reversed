extern "C" void FUN_00408bf0(std::uint32_t* param_1, std::uint32_t param_2, char param_3)
{
    if ((param_2 != 0) &&
        (*param_1 != 0) &&
        (((*reinterpret_cast<std::uint8_t*>(param_2 + sizeof(std::uint32_t)) & 1) != 0) || (param_3 != '\0')))
    {
        const std::uint32_t state = FUN_00407d70();
        const std::uint16_t flags = *reinterpret_cast<std::uint16_t*>(state + 0x16);

        *reinterpret_cast<std::uint16_t*>(state + 0x16) = static_cast<std::uint16_t>(flags | 1);

        (*reinterpret_cast<void(__thiscall**)(void*)>(*reinterpret_cast<std::uint32_t*>(param_2) + 4))(param_1);

        *reinterpret_cast<std::uint16_t*>(state + 0x16) =
            static_cast<std::uint16_t>((static_cast<std::uint8_t>(flags) & 1) |
                                       (*reinterpret_cast<std::uint16_t*>(state + 0x16) & 0xfffe));

        if ((*reinterpret_cast<std::int32_t*>(state + 0x0c) != 0) && ((flags & 1) == 0))
        {
            FUN_00408af0();
            return;
        }
    }

    return;
}