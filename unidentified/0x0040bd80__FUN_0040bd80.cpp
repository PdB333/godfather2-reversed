extern "C" void __fastcall FUN_0040bd80(void* this_)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    const char enabled = *reinterpret_cast<char*>(self + 0x10);
    const std::uint32_t valueAt20 = *reinterpret_cast<std::uint32_t*>(self + 0x20);

    float factor;
    if (enabled != '\0') {
        if (*reinterpret_cast<float*>(self + 0x2c) < *reinterpret_cast<float*>(self + 0x18)) {
            factor = *reinterpret_cast<float*>(self + 0x2c) / *reinterpret_cast<float*>(self + 0x18);

            if (*reinterpret_cast<int*>(self + 0x14) != 0) {
                factor = DAT_00e2b1a4 - factor;
            }

            goto build_packet;
        }

        factor = DAT_00e2b1a4;
        if (*reinterpret_cast<int*>(self + 0x14) == 0) {
            goto build_packet;
        }
    }

    factor = 0.0f;

build_packet:
    auto* const writeCursor = reinterpret_cast<int*>(DAT_01206880 + 0x14);

    **reinterpret_cast<void***>(DAT_01206880 + 0x14) = &PTR_LAB_0110af28;
    *writeCursor = *writeCursor + 4;

    auto* const packet = reinterpret_cast<std::uint8_t*>((*writeCursor + 3U) & 0xfffffffc);
    *writeCursor = reinterpret_cast<int>(packet);

    *reinterpret_cast<char*>(packet + 0x00) = enabled;
    *reinterpret_cast<std::uint32_t*>(packet + 0x01) = valueAt20;
    *reinterpret_cast<float*>(packet + 0x08) = factor;

    *writeCursor = *writeCursor + 0x0c;
}