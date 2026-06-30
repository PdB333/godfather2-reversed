void FUN_00402ba0()
{
    std::uint32_t index = 0;

    if (*reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xEC) != 0) {
        do {
            if (*reinterpret_cast<int*>(unaff_ESI + 0x78 + index * 4) == unaff_EDI) {
                if (index != 0xFFFFFFFFu) {
                    return;
                }
                break;
            }

            index = index + 1;
        } while (index < *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xEC));
    }

    const int entry = FUN_004025a0(unaff_EDI);
    if ((entry == 0) || (*reinterpret_cast<int*>(entry + 0x24) != 3)) {
        *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x60) =
            *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x60) |
            1 << (static_cast<std::uint8_t>(*reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xEC)) & 0x1F);
    }

    if (*reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xEC) < 0x1D) {
        *reinterpret_cast<int*>(unaff_ESI + 0x78 + *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0xEC) * 4) = unaff_EDI;
        *reinterpret_cast<int*>(unaff_ESI + 0xEC) = *reinterpret_cast<int*>(unaff_ESI + 0xEC) + 1;
    }
}