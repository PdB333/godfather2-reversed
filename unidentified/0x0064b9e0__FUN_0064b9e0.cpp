extern "C" std::uint32_t __thiscall FUN_0064b9e0(void* this_, std::uint32_t bitCount, std::uint8_t* outBuffer)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    if (bitCount == 0) {
        return 1;
    }

    const std::uint32_t bitPosition =
        *reinterpret_cast<std::uint32_t*>(self + 0x18);

    if (*reinterpret_cast<std::uint32_t*>(self + 0x2c) < bitPosition + bitCount) {
        *reinterpret_cast<std::uint8_t*>(self + 0x1c) = 1;
        return 0;
    }

    const std::uint32_t bitOffset = bitPosition & 7;
    std::uint8_t* sourceByte =
        reinterpret_cast<std::uint8_t*>(
            reinterpret_cast<std::uintptr_t>(*reinterpret_cast<void**>(self + 0x0c)) + (bitPosition >> 3)
        );
    std::uint32_t byteCount = bitCount + 7 >> 3;

    if (bitOffset == 0) {
        for (; byteCount != 0; --byteCount) {
            *outBuffer = *sourceByte;
            ++outBuffer;
            ++sourceByte;
        }

        *reinterpret_cast<std::uint32_t*>(self + 0x18) =
            *reinterpret_cast<std::uint32_t*>(self + 0x18) + bitCount;
        return 1;
    }

    std::uint8_t currentBits = static_cast<std::uint8_t>(*sourceByte >> static_cast<std::int8_t>(bitOffset));
    *reinterpret_cast<std::uint32_t*>(self + 0x18) = bitPosition + bitCount;

    const std::uint8_t leftShift = static_cast<std::uint8_t>(8 - bitOffset);
    std::uint8_t* writePtr = outBuffer;

    if (7 < bitCount) {
        std::uint8_t* loopWritePtr = outBuffer;
        auto remainingWholeBytes = reinterpret_cast<std::uint8_t*>(bitCount >> 3);
        std::uint8_t previousBits = currentBits;

        do {
            std::uint8_t* const nextSourceByte = sourceByte + 1;
            sourceByte = sourceByte + 1;
            currentBits = static_cast<std::uint8_t>(*nextSourceByte >> static_cast<std::int8_t>(bitOffset));
            writePtr = loopWritePtr + 1;
            bitCount = bitCount - 8;
            remainingWholeBytes = reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uintptr_t>(remainingWholeBytes) - 1
            );
            *loopWritePtr = static_cast<std::uint8_t>(*nextSourceByte << (leftShift & 0x1f) | previousBits);
            loopWritePtr = writePtr;
            previousBits = currentBits;
        } while (remainingWholeBytes != reinterpret_cast<std::uint8_t*>(0));
    }

    if (bitCount != 0) {
        if (bitCount <= 8 - bitOffset) {
            *writePtr = currentBits;
            return 1;
        }

        *writePtr = static_cast<std::uint8_t>(sourceByte[1] << (leftShift & 0x1f) | currentBits);
    }

    return 1;
}