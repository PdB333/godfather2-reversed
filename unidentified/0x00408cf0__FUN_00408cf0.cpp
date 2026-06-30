extern "C" void FUN_00408cf0(std::uint32_t /*param_1*/, std::uint8_t param_2)
{
    auto* entry = *reinterpret_cast<std::uint32_t**>(
        DAT_01162380 + (DAT_0120e93c & 0x0fff) * sizeof(std::uint32_t));

    while ((entry != nullptr) && (entry[4] != DAT_0120e93c))
    {
        entry = reinterpret_cast<std::uint32_t*>(*entry);
    }

    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(entry) + 0x16) =
        static_cast<std::uint16_t>((param_2 & 1) |
                                   (*reinterpret_cast<std::uint16_t*>(
                                        reinterpret_cast<std::uintptr_t>(entry) + 0x16) &
                                    0xfffe));

    if ((entry[3] != 0) && (param_2 == 0))
    {
        FUN_00408af0();
        return;
    }

    return;
}