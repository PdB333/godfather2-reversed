extern "C" void __fastcall FUN_00653c20(std::int32_t* this_, std::int32_t elapsed)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this_);

    if ((*reinterpret_cast<std::uint8_t*>(self + 0xb8) & 0x0c) == 0) {
        if (static_cast<std::uint32_t>((*reinterpret_cast<std::int32_t*>(self + 0xc4) -
                                        *reinterpret_cast<std::int32_t*>(self + 0xbc)) +
                                       elapsed) <
            static_cast<std::uint32_t>(*reinterpret_cast<std::int32_t*>(self + 0xfc))) {
            return;
        }

        std::uint32_t uVar4 =
            static_cast<std::uint32_t>(((*reinterpret_cast<std::int32_t*>(self + 0xc4) -
                                         *reinterpret_cast<std::int32_t*>(self + 0xbc)) -
                                        *reinterpret_cast<std::int32_t*>(self + 0xfc)) +
                                       elapsed);
        *reinterpret_cast<std::uint32_t*>(self + 0xc4) = uVar4;

        if (1000 < uVar4) {
            *reinterpret_cast<std::int32_t*>(self + 0xc4) = 1000;
        }
    }

    reinterpret_cast<void(__thiscall*)(void*)>(
        *reinterpret_cast<std::int32_t*>(*reinterpret_cast<std::int32_t*>(self) + 0x34))(this_);

    char cVar3 = FUN_00653da0();

    if ((cVar3 == '\0') &&
        ((cVar3 = reinterpret_cast<char(__thiscall*)(void*)>(
              *reinterpret_cast<std::int32_t*>(*reinterpret_cast<std::int32_t*>(self) + 0x54))(this_)),
         cVar3 != '\0')) {
        *reinterpret_cast<std::int32_t*>(self + 0xbc) = elapsed;
        FUN_006530a0(0);
        FUN_00653df0();
        FUN_0064b440();
        return;
    }

    if ((*reinterpret_cast<std::uint8_t*>(self + 0xb8) & 0x0c) != 0) {
        const std::int32_t iVar1 = *reinterpret_cast<std::int32_t*>(self + 0x90);
        const std::int32_t iVar5 = iVar1 - *reinterpret_cast<std::int32_t*>(self + 0x1c0);

        float fVar2 = static_cast<float>(elapsed - *reinterpret_cast<std::int32_t*>(self + 0x1c4));
        if (elapsed - *reinterpret_cast<std::int32_t*>(self + 0x1c4) < 0) {
            fVar2 = fVar2 + DAT_00e44578;
        }

        if ((((1.0f < static_cast<float>(iVar5) * DAT_00e35654 * fVar2 * DAT_00e3ac54) ||
              (_DAT_00e44960 < static_cast<double>(iVar5)))) &&
             (*reinterpret_cast<std::int32_t*>(self + 0x1c0) != iVar1))) {
            *reinterpret_cast<std::int32_t*>(self + 0x1c0) = iVar1;
            *reinterpret_cast<std::int32_t*>(self + 0x1c4) = elapsed;
            FUN_00653a60();
        }
    }
}