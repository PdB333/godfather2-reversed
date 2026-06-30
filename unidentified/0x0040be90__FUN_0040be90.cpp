extern "C" void __fastcall FUN_0040be90(void* this_)
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
    const std::uint32_t valueAt1c = *reinterpret_cast<std::uint32_t*>(self + 0x1c);

    auto* const writeCursor = reinterpret_cast<std::int32_t*>(DAT_01206880 + 0x14);

    **reinterpret_cast<void***>(DAT_01206880 + 0x14) = &PTR_LAB_0110af3c;
    *writeCursor = *writeCursor + 4;

    auto* packet = reinterpret_cast<std::uint64_t*>((*writeCursor + 3U) & 0xfffffffc);
    *writeCursor = static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(packet));

    *packet = CONCAT35(uStack_b, CONCAT41(valueAt20, enabled));
    packet[1] = CONCAT44(valueAt1c, factor);

    *writeCursor = *writeCursor + 0x10;
}