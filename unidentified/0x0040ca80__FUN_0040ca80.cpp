extern "C" void FUN_0040ca80(int param_1)
{
    std::uint32_t count = 0;

    if (*reinterpret_cast<int*>(unaff_EDI + 0x0C) != 0) {
        do {
            auto* node = reinterpret_cast<std::uint32_t*>(FUN_009c8e50(0x20));

            if (node == nullptr) {
                node = nullptr;
            } else {
                FUN_0049c2c0(*reinterpret_cast<std::uint32_t*>(unaff_EDI + 0x08));
                node[7] = 0;
                node[0] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e337b4);
            }

            node[7] = 0;

            if (*reinterpret_cast<int*>(param_1 + 0x0C) == 0) {
                *reinterpret_cast<std::uint32_t**>(param_1 + 0x08) = node;
            } else {
                *reinterpret_cast<std::uint32_t**>(*reinterpret_cast<int*>(param_1 + 0x0C) + 0x1C) = node;
            }

            *reinterpret_cast<std::uint32_t**>(param_1 + 0x0C) = node;

            FUN_00ab51e0(1);
            count = count + 1;
        } while (count < *reinterpret_cast<std::uint32_t*>(unaff_EDI + 0x0C));
    }
}