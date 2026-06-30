extern "C" std::uint32_t __fastcall FUN_00653da0(void* this_)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this_);

    const std::uint32_t value = static_cast<std::uint32_t>(
        *reinterpret_cast<std::int32_t*>(self + 0x98) -
        *reinterpret_cast<std::int32_t*>(self + 0x94));

    if (0x1d < value) {
        return (value & 0xffffff00u) | 1u;
    }

    if ((*reinterpret_cast<std::uint8_t*>(self + 0xb8) & 0x0c) != 0) {
        float thresholdValue = static_cast<float>(static_cast<std::int32_t>(value));
        if (static_cast<std::int32_t>(value) < 0) {
            thresholdValue = thresholdValue + DAT_00e44578;
        }

        if (*reinterpret_cast<float*>(self + 0x1b8) <= thresholdValue) {
            return 1;
        }

        return 0;
    }

    return value & 0xffffff00u;
}