extern "C" void FUN_00654f70(int param_1, std::uint64_t* param_2, int param_3, int param_4)
{
    const std::uint32_t size = static_cast<std::uint32_t>(*reinterpret_cast<int*>(param_3 + 0x18) + 7U) >> 3;
    auto* node = reinterpret_cast<std::int32_t*>(_malloc(size + 0x24));

    *reinterpret_cast<std::uint64_t*>(node + 1) = param_2[0];
    *reinterpret_cast<std::uint64_t*>(node + 3) = param_2[1];
    node[5] = *reinterpret_cast<int*>(param_2 + 2);

    const int baseValue = *reinterpret_cast<int*>(param_1 + 100);
    node[7] = static_cast<int>(size);
    node[6] = baseValue + param_4;

    _memcpy(node + 8, *reinterpret_cast<void**>(param_3 + 0x0C), size);

    auto* insertAfter = reinterpret_cast<std::int32_t*>(param_1 + 0x80);
    if (*reinterpret_cast<std::int32_t**>(param_1 + 0x80) != nullptr) {
        auto* current = *reinterpret_cast<std::int32_t**>(param_1 + 0x80);
        do {
            auto* previous = current;
            if (static_cast<std::uint32_t>(node[6]) <= static_cast<std::uint32_t>(previous[6])) {
                break;
            }

            current = reinterpret_cast<std::int32_t*>(*previous);
            insertAfter = previous;
        } while (reinterpret_cast<std::int32_t*>(*previous) != nullptr);
    }

    *node = *insertAfter;
    *insertAfter = reinterpret_cast<int>(node);
}