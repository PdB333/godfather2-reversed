void FUN_00402b00(int param_1)
{
    const auto value = unaff_ESI;
    std::uint32_t count = *reinterpret_cast<std::uint32_t*>(param_1 + 0x74);
    std::uint32_t index = 0;

    if (count != 0) {
        do {
            if (*reinterpret_cast<int*>(param_1 + 100 + index * 4) == value) {
                if (index != 0xFFFFFFFFu) {
                    return;
                }
                break;
            }

            index = index + 1;
        } while (index < count);
    }

    if (count < 4) {
        *reinterpret_cast<int*>(param_1 + 100 + count * 4) = value;
        *reinterpret_cast<int*>(param_1 + 0x74) = *reinterpret_cast<int*>(param_1 + 0x74) + 1;
    }
}