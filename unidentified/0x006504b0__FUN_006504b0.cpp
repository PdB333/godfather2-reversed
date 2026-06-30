extern "C" void __thiscall FUN_006504b0(std::int32_t* this_)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this_);
    auto** const heap = *reinterpret_cast<std::int32_t***>(self + 0x1fc);

    if (heap != nullptr) {
        ++*reinterpret_cast<std::int32_t*>(self + 0x20c);

        std::int32_t slotOffset = 0;
        std::int32_t entryOffset = 0;
        std::int32_t index = 2;

        do {
            heap[slotOffset / 4] = reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(self + 0x214) + entryOffset
            );
            *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(heap[slotOffset / 4]) + 0x2c
            ) = index + -2;

            heap[(slotOffset + 4) / 4] = reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(self + 0x214) + entryOffset + 0x30
            );
            *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(heap[(slotOffset + 4) / 4]) + 0x2c
            ) = index + -1;

            heap[(slotOffset + 8) / 4] = reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(self + 0x214) + entryOffset + 0x60
            );
            *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(heap[(slotOffset + 8) / 4]) + 0x2c
            ) = index;

            heap[(slotOffset + 0xc) / 4] = reinterpret_cast<std::int32_t*>(
                *reinterpret_cast<std::int32_t*>(self + 0x214) + entryOffset + 0x90
            );
            *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(heap[(slotOffset + 0xc) / 4]) + 0x2c
            ) = index + 1;

            const std::int32_t nextIndex = index + 2;
            entryOffset = entryOffset + 0xc0;
            slotOffset = slotOffset + 0x10;
            index = index + 4;
        } while (nextIndex < 0x400);

        *reinterpret_cast<std::uint8_t*>(self + 0x209) = 1;
        FUN_00650680(this_, *reinterpret_cast<std::int32_t*>(self + 0x20c));
    }
}