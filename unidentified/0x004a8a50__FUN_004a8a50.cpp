extern "C" void __thiscall FUN_004a8a50(void* this_, int param_2, int param_3)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    const std::uint32_t bitIndex = *reinterpret_cast<std::uint32_t*>(param_3 + 0x18);

    bool hasBit = false;
    if (*reinterpret_cast<std::uint32_t*>(param_3 + 0x2c) < bitIndex) {
        *reinterpret_cast<std::uint8_t*>(param_3 + 0x1c) = 1;
        hasBit = false;
    } else {
        hasBit =
            (*reinterpret_cast<std::uint8_t*>(
                 (bitIndex >> 3) + *reinterpret_cast<int*>(param_3 + 0x0c)) &
             static_cast<std::uint8_t>(1u << (static_cast<std::uint8_t>(bitIndex) & 7))) != 0;
        *reinterpret_cast<std::uint32_t*>(param_3 + 0x18) = bitIndex + 1;
    }

    if ((*reinterpret_cast<int*>(self + 0x40) == 0) && hasBit) {
        auto* const key = reinterpret_cast<std::uint32_t*>(self + 0x48);

        FUN_0064b9e0(0x40, key);
        FUN_0064b9e0(0x20, self + 0x50);

        const int existing = FUN_004544a0(key[0], key[1]);
        if (existing == 0) {
            DAT_0120540c = reinterpret_cast<int>(self);
            const int created =
                (**reinterpret_cast<int (***)(std::uint32_t, std::uint32_t, int)>(
                    *reinterpret_cast<int*>(self + 0x44) + 0x74))(key[0], key[1], param_3);
            *reinterpret_cast<int*>(self + 0x40) = created;
            DAT_0120540c = 0;
        } else {
            const char accepted =
                (**reinterpret_cast<char (***)(int, int, void*)>(*DAT_0122344c + 4))(existing, param_2, self);

            if (accepted == '\0') {
                int* const previousOwner = *reinterpret_cast<int**>(existing + 0x0c);

                *reinterpret_cast<int*>(self + 0x40) = existing;
                *reinterpret_cast<int*>(existing + 0x0c) = reinterpret_cast<int>(self);

                if (previousOwner != nullptr) {
                    previousOwner[0x10] = 0;

                    if ((previousOwner[0x0f] & 1U) == 0) {
                        previousOwner[0x0f] = previousOwner[0x0f] | 1;
                        FUN_0064d670();
                        FUN_004a8900(param_2);
                    }

                    if ((((std::uint32_t)previousOwner[0x0c] >> 1) & 1) == 0) {
                        (**reinterpret_cast<void (***)(int)>(*previousOwner + 4))(1);
                    }
                }
            } else {
                *reinterpret_cast<std::uint32_t*>(self + 0x3c) =
                    *reinterpret_cast<std::uint32_t*>(self + 0x3c) | 1;
                FUN_0064d670();
                FUN_004a8900(param_2);
            }
        }
    }

    int* const handler = *reinterpret_cast<int**>(self + 0x40);
    if (handler != nullptr) {
        if ((*reinterpret_cast<std::uint8_t*>(self + 0x3c) & 1) != 0) {
            (**reinterpret_cast<void (***)(int)>(*handler + 0x24))(param_2);
            return;
        }

        (**reinterpret_cast<void (***)(int)>(*handler + 0x20))(param_2);
        return;
    }

    (**reinterpret_cast<void (***)(int)>(*reinterpret_cast<int*>(self + 0x44) + 0x78))(param_3);
}