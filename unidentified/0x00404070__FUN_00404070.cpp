void __fastcall FUN_00404070(int param_1)
{
    if (unaff_EDI != 0) {
        const std::uint32_t count = *reinterpret_cast<std::uint32_t*>(param_1 + 0x124);
        std::uint32_t index = 0;
        std::uint32_t foundIndex = 0xffffffff;

        if (count != 0) {
            do {
                foundIndex = index;

                if (*reinterpret_cast<int*>(param_1 + 0xa4 + index * 4) == unaff_EDI) {
                    break;
                }

                index = index + 1;
                foundIndex = 0xffffffff;
            } while (index < count);
        }

        if (foundIndex < count) {
            if (foundIndex < count - 1) {
                *reinterpret_cast<std::uint32_t*>(param_1 + 0xa4 + foundIndex * 4) =
                    *reinterpret_cast<std::uint32_t*>(param_1 + 0xa0 + count * 4);
            }

            *reinterpret_cast<int*>(param_1 + 0x124) =
                *reinterpret_cast<int*>(param_1 + 0x124) + -1;
        }

        int* piVar3 = reinterpret_cast<int*>(FUN_009c8f80());
        (**reinterpret_cast<void (***)(void)>( *piVar3 + 4))();
    }

    return;
}