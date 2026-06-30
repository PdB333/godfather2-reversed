std::uint32_t __thiscall FUN_00402f40(std::uint32_t* param_1, std::uint32_t param_2, char param_3)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this);

    *reinterpret_cast<std::uint32_t*>(self + 0x38) = param_2;
    *reinterpret_cast<std::int32_t*>(self + 0x40) = reinterpret_cast<std::int32_t>(self);
    *reinterpret_cast<std::uint32_t*>(self + 0x3c) = 0;

    if (param_3 != '\0') {
        *reinterpret_cast<std::uint32_t*>(self + 0x44) = 0;
    }

    std::uint32_t local_c = *param_1;
    std::int32_t local_8 = reinterpret_cast<std::int32_t>(self + 0x34);
    std::uint8_t local_4 = 0;

    FUN_00408a00(&local_c, 1);

    std::uint16_t currentHandler = *reinterpret_cast<std::uint16_t*>(self + 0x56);
    std::uint32_t currentValue = local_c;

    while (currentHandler != 0xffff) {
        const std::uint32_t handlerIndex = static_cast<std::uint32_t>(currentHandler);
        currentHandler = (&DAT_01161380)[handlerIndex * 4];

        if (((*reinterpret_cast<std::uint16_t*>(
                  reinterpret_cast<std::uint8_t*>(&DAT_01161382) + handlerIndex * 8) &
              static_cast<std::uint16_t>(param_2)) != 0) &&
            ((*reinterpret_cast<std::int32_t**>(
                  reinterpret_cast<std::uint8_t*>(&DAT_01161384) + handlerIndex * 8)) != nullptr) &&
            (currentValue != 0)) {

            std::int32_t* const piVar3 =
                *reinterpret_cast<std::int32_t**>(
                    reinterpret_cast<std::uint8_t*>(&DAT_01161384) + handlerIndex * 8);

            auto* puVar4 =
                *reinterpret_cast<std::uint32_t**>(DAT_01162380 + (currentValue & 0xfff) * 4);

            while ((puVar4 != nullptr) && (puVar4[4] != currentValue)) {
                puVar4 = reinterpret_cast<std::uint32_t*>(*puVar4);
            }

            const std::uint16_t oldFlags =
                *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(puVar4) + 0x16);

            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(puVar4) + 0x16) =
                oldFlags | 1;

            // Correct function pointer call: (**(code **)(*piVar3 + 4))(&local_c);
            auto fn = *reinterpret_cast<void (**)(std::uint32_t*)>(
                reinterpret_cast<std::uint8_t*>(*piVar3) + 4);
            fn(&local_c);

            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(puVar4) + 0x16) =
                static_cast<std::uint16_t>(static_cast<std::uint8_t>(oldFlags) & 1) |
                (*reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(puVar4) + 0x16) &
                 0xfffe);

            currentValue = local_c;

            if ((puVar4[3] != 0) && ((oldFlags & 1) == 0)) {
                FUN_00408af0();
                currentValue = local_c;
            }
        }
    }

    *reinterpret_cast<std::int32_t*>(self + 0x44) =
        *reinterpret_cast<std::int32_t*>(self + 0x44) + 1;

    return *reinterpret_cast<std::uint32_t*>(self + 0x3c);
}