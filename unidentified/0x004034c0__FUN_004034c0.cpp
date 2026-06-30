void __thiscall FUN_004034c0(std::uint32_t thisPtr)
{
    auto* current = *reinterpret_cast<std::uint32_t**>(thisPtr + 0x70);

    while (current != nullptr) {
        auto* node = current;
        current = reinterpret_cast<std::uint32_t*>(*node);

        if ((((static_cast<std::uint32_t>(node[0x14]) >> 7) & 1u) == 0u)) {
            FUN_004048c0(node, 0);
        }
    }

    current = *reinterpret_cast<std::uint32_t**>(thisPtr + 0x68);

    do {
        while (true) {
            if (current == nullptr) {
                return;
            }

            if ((((static_cast<std::uint32_t>(current[0x14]) >> 7) & 1u) == 0u)) {
                break;
            }

            current = reinterpret_cast<std::uint32_t*>(*current);
        }

        if (*reinterpret_cast<std::int16_t*>(current + 0x15) != 0) {
            FUN_004048c0(current, 0);
            current = reinterpret_cast<std::uint32_t*>(*current);
            continue;
        }

        FUN_004048c0(current, 0);
        current = *reinterpret_cast<std::uint32_t**>(thisPtr + 0x68);
    } while (true);
}