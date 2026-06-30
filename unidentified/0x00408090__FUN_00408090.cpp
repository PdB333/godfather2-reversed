extern "C" void __fastcall FUN_00408090(std::uint32_t* param_1)
{
    auto* node = *reinterpret_cast<std::uint32_t**>(
        DAT_01162380 + ((*param_1 & 0x0fff) * 4)
    );

    while (node != nullptr && node[4] != *param_1) {
        node = reinterpret_cast<std::uint32_t*>(*node);
    }

    --*reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uint8_t*>(node) + 0x14);
    --*reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 0x06);

    if (*reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 0x06) == 0) {
        *param_1 = 0;
    }
}