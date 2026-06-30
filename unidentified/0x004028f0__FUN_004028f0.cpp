uint32_t __fastcall FUN_004028f0(uint32_t /*param_1*/, uint16_t param_2)
{
    uint32_t index = static_cast<uint32_t>(param_2);
    uint32_t current = 0xFFFF;

    if (param_2 != 0xFFFF) {
        do {
            current = index;

            if (*reinterpret_cast<int*>(0x01161384 + current * 8) == unaff_ESI) {
                break;
            }

            index = static_cast<uint32_t>(
                *reinterpret_cast<uint16_t*>(0x01161380 + current * 8)
            );

            if (*reinterpret_cast<uint16_t*>(0x01161380 + current * 8) == 0xFFFF) {
                return 0xFFFF;
            }
        } while (true);
    }

    return current;
}