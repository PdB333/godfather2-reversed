extern "C" void __fastcall FUN_006555b0(void* this_)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this_);

    const std::uint32_t now = FUN_0065c190();
    *reinterpret_cast<std::uint32_t*>(self + 0x64) = now;

    FUN_0065ca60();

    auto* node = *reinterpret_cast<std::int32_t**>(self + 0x80);
    while ((node != nullptr) &&
           (static_cast<std::uint32_t>(node[6]) <
            *reinterpret_cast<std::uint32_t*>(self + 0x64))) {
        auto* const next = reinterpret_cast<std::int32_t*>(*node);

        FUN_00658230(
            self + 0x5c,
            node + 8,
            node[7],
            0);

        free(node);
        *reinterpret_cast<std::int32_t**>(self + 0x80) = next;

        node = *reinterpret_cast<std::int32_t**>(self + 0x80);
    }

    FUN_0064d6e0();

    std::int32_t i = 0;
    if (0 < *reinterpret_cast<std::int32_t*>(self + 0x0c)) {
        do {
            FUN_00653c20();
            i = i + 1;
        } while (i < *reinterpret_cast<std::int32_t*>(self + 0x0c));
    }

    if (*reinterpret_cast<std::uint32_t*>(self + 0x6c) + 0x5dcu <
        *reinterpret_cast<std::uint32_t*>(self + 0x64)) {
        i = 0;
        *reinterpret_cast<std::uint32_t*>(self + 0x6c) =
            *reinterpret_cast<std::uint32_t*>(self + 0x64);

        if (0 < *reinterpret_cast<std::int32_t*>(self + 0x0c)) {
            do {
                FUN_00652fe0();
                i = i + 1;
            } while (i < *reinterpret_cast<std::int32_t*>(self + 0x0c));
        }
    }
}