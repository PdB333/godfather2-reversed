extern "C" void __thiscall FUN_004087c0(void* const param_1)
{
    if ((
            *reinterpret_cast<const std::uint8_t*>(
                static_cast<std::uint8_t*>(param_1) + sizeof(void*)
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
        local.field_4 = param_1;
        local.field_8 = 0;

        (*reinterpret_cast<void(__thiscall**)(void*)>(
            *reinterpret_cast<std::uint32_t*>(param_1) + 4
        ))(&local);
    }

    (*reinterpret_cast<void(__thiscall**)(int)>(
        *reinterpret_cast<std::uint32_t*>(param_1)
    ))(1);
}