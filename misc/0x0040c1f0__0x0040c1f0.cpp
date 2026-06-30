extern "C" void __thiscall FUN_0040c1f0(
    void* this_,
    std::uint32_t valueAt64,
    float duration,
    char flag,
    std::uint32_t mask)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    *reinterpret_cast<std::uint32_t*>(self + 0x50) =
        *reinterpret_cast<std::uint32_t*>(self + 0x50) | mask;

    if (*reinterpret_cast<char*>(self + 0x54) != '\0') {
        if (*reinterpret_cast<float*>(self + 0x5c) <= *reinterpret_cast<float*>(self + 0x70)) {
            if (*reinterpret_cast<int*>(self + 0x58) == 0) {
                (*reinterpret_cast<void(__thiscall***)(void*)>(self + 0x44))[0][1](
                    *reinterpret_cast<void**>(self + 0x44));
                return;
            }
        } else {
            float factor =
                *reinterpret_cast<float*>(self + 0x70) / *reinterpret_cast<float*>(self + 0x5c);

            if (*reinterpret_cast<int*>(self + 0x58) != 0) {
                factor = DAT_00e2b1a4 - factor;
            }

            if (factor == DAT_00e2b1a4) {
                (*reinterpret_cast<void(__thiscall***)(void*)>(self + 0x44))[0][1](
                    *reinterpret_cast<void**>(self + 0x44));
                return;
            }
        }
    }

    *reinterpret_cast<std::uint32_t*>(self + 0x64) = valueAt64;
    *reinterpret_cast<char*>(self + 0x74) = flag;
    *reinterpret_cast<std::uint32_t*>(self + 0x70) = 0;
    *reinterpret_cast<float*>(self + 0x5c) = duration;
    *reinterpret_cast<std::int32_t*>(self + 0x58) = 0;
    *reinterpret_cast<std::uint8_t*>(self + 0x55) = 1;
    *reinterpret_cast<std::uint8_t*>(self + 0x54) = 1;
    *reinterpret_cast<std::uint8_t*>(self + 0x68) = 0;

    FUN_0040b7a0();

    auto* const packetCursor = reinterpret_cast<std::uint32_t*>(DAT_01206880 + 0x14);
    *reinterpret_cast<void**>(*packetCursor) = &PTR_LAB_0110af78;
    *packetCursor = *packetCursor + 4;
    *reinterpret_cast<bool*>(*packetCursor) = flag != '\0';
    *packetCursor = *packetCursor + 4 & 0xfffffffc;
}