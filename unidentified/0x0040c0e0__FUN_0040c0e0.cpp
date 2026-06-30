extern "C" void __fastcall FUN_0040c0e0(void* this_)
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
    int* const packetCursor = reinterpret_cast<int*>(DAT_01206880 + 0x14);
    const std::uint32_t valueAt30 = *reinterpret_cast<std::uint32_t*>(self + 0x30);

    *reinterpret_cast<void***>(*packetCursor) = &PTR_LAB_0110af64;
    *packetCursor += 4;

    auto* const payload = reinterpret_cast<std::uint64_t*>((*packetCursor + 3U) & 0xfffffffc);
    *packetCursor = reinterpret_cast<int>(payload);

    *payload = CONCAT35(uStack_f, CONCAT41(valueAt20, enabled));
    payload[1] = CONCAT44(valueAt1c, factor);
    *reinterpret_cast<std::uint32_t*>(payload + 2) = valueAt30;

    *packetCursor += 0x14;
}