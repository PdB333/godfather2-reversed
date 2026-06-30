extern "C" void __fastcall FUN_00653800(void* this_)
{
    auto* const self = static_cast<std::uint8_t*>(this_);
    auto* const bitReader = reinterpret_cast<std::uint8_t*>(_ESI);

    const std::uint32_t bitIndex = *reinterpret_cast<std::uint32_t*>(bitReader + 0x18);
    if (*reinterpret_cast<std::uint32_t*>(bitReader + 0x2c) < bitIndex) {
        *reinterpret_cast<std::uint8_t*>(bitReader + 0x1c) = 1;
        return;
    }

    const std::uint8_t firstByte =
        *reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(*reinterpret_cast<int*>(bitReader + 0x0c)) + (bitIndex >> 3));

    const std::uint32_t nextBitIndex = bitIndex + 1;
    *reinterpret_cast<std::uint32_t*>(bitReader + 0x18) = nextBitIndex;

    if ((firstByte & static_cast<std::uint8_t>(1 << (static_cast<std::uint8_t>(bitIndex) & 7))) != 0) {
        if (*reinterpret_cast<std::uint32_t*>(bitReader + 0x2c) < nextBitIndex) {
            *reinterpret_cast<std::uint8_t*>(bitReader + 0x1c) = 1;
        } else {
            const std::uint8_t secondByte =
                *reinterpret_cast<std::uint8_t*>(
                    reinterpret_cast<std::uintptr_t>(*reinterpret_cast<int*>(bitReader + 0x0c)) + (nextBitIndex >> 3));

            *reinterpret_cast<std::uint32_t*>(bitReader + 0x18) = bitIndex + 2;

            if ((secondByte & static_cast<std::uint8_t>(1 << (static_cast<std::uint8_t>(nextBitIndex) & 7))) != 0) {
                *reinterpret_cast<std::uint32_t*>(self + 0xb8) =
                    *reinterpret_cast<std::uint32_t*>(self + 0xb8) | 8;
                return;
            }
        }

        *reinterpret_cast<std::uint32_t*>(self + 0xf0) = FUN_00652840(bitReader);
        *reinterpret_cast<std::uint32_t*>(self + 0xec) = FUN_00652840(bitReader);
        *reinterpret_cast<std::uint32_t*>(self + 0xe8) = FUN_00652840(bitReader);
        *reinterpret_cast<std::uint32_t*>(self + 0xe4) = FUN_00652840(bitReader);
        FUN_006538d0();
    }
}