extern "C" void __fastcall FUN_0040bc40(void* this_)
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
    std::uint32_t contextValue;
    if (*reinterpret_cast<int*>(DAT_0122339c + 0x154) == 0) {
        const int tebLike = *reinterpret_cast<int*>(unaff_FS_OFFSET + 0x2c);
        contextValue = *reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(tebLike) + 0x24);
    } else {
        contextValue = *reinterpret_cast<std::uint32_t*>(DAT_0122339c + 0x14);
    }

    auto* const streamCursor = reinterpret_cast<int*>(DAT_01206880 + 0x14);

    *reinterpret_cast<void**>(*reinterpret_cast<int*>(DAT_01206880 + 0x14)) = &PTR_LAB_0110af14;
    *streamCursor = *streamCursor + 4;

    auto* const payload =
        reinterpret_cast<std::uint8_t*>((*streamCursor + 3U) & 0xfffffffc);
    *streamCursor = reinterpret_cast<int>(payload);

    payload[0] = static_cast<std::uint8_t>(enabled);
    *reinterpret_cast<std::uint32_t*>(payload + 1) = valueAt20;
    *reinterpret_cast<float*>(payload + 8) = factor;

    *streamCursor = *streamCursor + 0x0c;
    *reinterpret_cast<std::uint32_t*>(*streamCursor) = contextValue;
    *streamCursor = *streamCursor + 4;
}