extern "C" void FUN_00408800()
{
    auto* const hashKey = reinterpret_cast<std::uint32_t*>(EAX);
    auto* node = reinterpret_cast<std::int32_t*>(
        *reinterpret_cast<std::uint32_t*>(
            DAT_01162380 + ((*hashKey & 0x0fff) * 4)
        )
    );

    if (node != nullptr)
    {
        while (static_cast<std::uint32_t>(node[4]) != *hashKey)
        {
            node = reinterpret_cast<std::int32_t*>(node[0]);
            if (node == nullptr)
            {
                return;
            }
        }

        if ((node != nullptr) && (node[1] != 0))
        {
            int listHead = *reinterpret_cast<std::int32_t*>(node[1] + 8);

            while (listHead != 0)
            {
                auto* const object = *reinterpret_cast<std::int32_t**>(listHead + 0x0c);

                if ((
                        *reinterpret_cast<std::uint8_t*>(
                            reinterpret_cast<std::uint8_t*>(object) + sizeof(void*)
                        ) & 0x02
                    ) != 0)
                {
                    struct CallbackParam
                    {
                        std::uint32_t field_0;
                        void* field_4;
                        std::uint8_t field_8;
                    };

                    CallbackParam local{};
                    local.field_0 = DAT_012067dc;
                    local.field_4 = object;
                    local.field_8 = 0;

                    (*reinterpret_cast<void(__thiscall**)(void*)>(
                        *reinterpret_cast<std::uint32_t*>(object) + 4
                    ))(&local);
                }

                (*reinterpret_cast<void(__thiscall**)(int)>(
                    *reinterpret_cast<std::uint32_t*>(object)
                ))(1);

                if (node[1] == 0)
                {
                    return;
                }

                listHead = *reinterpret_cast<std::int32_t*>(node[1] + 8);
            }
        }
    }
}