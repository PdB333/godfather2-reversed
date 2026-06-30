extern "C" std::uint32_t FUN_00408a00(std::uint32_t* param_1, char param_2)
{
    auto* entry = *reinterpret_cast<std::int32_t**>(
        DAT_01162380 + ((*param_1 & 0x0fffU) * 4)
    );

    std::uint32_t result = 0;

    if (entry != nullptr)
    {
        while (static_cast<std::uint32_t>(entry[4]) != *param_1)
        {
            entry = reinterpret_cast<std::int32_t*>(entry[0]);
            if (entry == nullptr)
            {
                return result;
            }
        }

        if (entry[1] != 0)
        {
            const std::uint32_t oldState = param_1[2];
            *reinterpret_cast<std::uint8_t*>(param_1 + 2) = 1;

            const std::uint16_t oldFlags = *reinterpret_cast<std::uint16_t*>(
                reinterpret_cast<std::uintptr_t>(entry) + 0x16
            );
            *reinterpret_cast<std::uint16_t*>(
                reinterpret_cast<std::uintptr_t>(entry) + 0x16
            ) = oldFlags | 1;

            auto* listHead = reinterpret_cast<std::int32_t*>(entry[1]);
            if (listHead != nullptr)
            {
                auto node = listHead[2];

                while (node != 0)
                {
                    do
                    {
                        if (((*reinterpret_cast<std::uint16_t*>(node + 0x14) & 0x8000) == 0) &&
                            (((*reinterpret_cast<std::uint8_t*>(
                                   *reinterpret_cast<std::int32_t*>(node + 0x0c) + 1
                               ) & 1) != 0) ||
                             (param_2 != '\0')))
                        {
                            (*reinterpret_cast<void(__cdecl**)(std::uint32_t*)>(
                                *reinterpret_cast<std::int32_t*>(
                                    *reinterpret_cast<std::int32_t*>(node + 0x0c)
                                ) + 4
                            ))(param_1);
                        }

                        node = *reinterpret_cast<std::int32_t*>(node + 4);
                    } while (node != 0);

                    if (listHead != nullptr)
                    {
                        listHead = reinterpret_cast<std::int32_t*>(listHead[0]);
                        if (listHead != nullptr)
                        {
                            node = listHead[2];
                        }
                    }
                }
            }

            *reinterpret_cast<std::uint16_t*>(
                reinterpret_cast<std::uintptr_t>(entry) + 0x16
            ) = static_cast<std::uint16_t>(
                (static_cast<std::uint8_t>(oldFlags) & 1) |
                (*reinterpret_cast<std::uint16_t*>(
                    reinterpret_cast<std::uintptr_t>(entry) + 0x16
                ) & 0xfffe)
            );

            if ((entry[3] != 0) && ((oldFlags & 1) == 0))
            {
                FUN_00408af0();
            }

            *reinterpret_cast<char*>(param_1 + 2) = static_cast<char>(oldState);
            result = 1;
        }
    }

    return result;
}