extern "C" void __fastcall FUN_0040bfb0(void* this_)
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

    auto* const writeCursor = reinterpret_cast<int*>(DAT_01206880 + 0x14);

    **reinterpret_cast<void***>(DAT_01206880 + 0x14) = &PTR_LAB_0110af50;
    *writeCursor = *writeCursor + 4;

    const std::uint32_t aligned = (*writeCursor + 3U) & 0xfffffffc;
    auto* const out = reinterpret_cast<std::uint64_t*>(static_cast<std::uintptr_t>(aligned));
    *writeCursor = static_cast<int>(reinterpret_cast<std::uintptr_t>(out));

    // Reconstruct CONCAT35(uStack_b, CONCAT41(uVar3, cVar2))
    // Layout:
    // byte 0: enabled
    // bytes 1-4: valueAt20
    // bytes 5-7: uStack_b (uninitialized 3 bytes)
    std::uint32_t uStack_b; // intentionally uninitialized (represents undefined3)
    const std::uint64_t first =
        (static_cast<std::uint64_t>(uStack_b & 0x00FFFFFF) << 40) |
        (static_cast<std::uint64_t>(valueAt20) << 8) |
        static_cast<std::uint8_t>(enabled);

    *out = first;

    out[1] =
        (static_cast<std::uint64_t>(valueAt1c) << 32) |
        static_cast<std::uint32_t>(std::bit_cast<std::uint32_t>(factor));

    *writeCursor = *writeCursor + 0x10;
}