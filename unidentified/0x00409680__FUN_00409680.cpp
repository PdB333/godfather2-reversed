extern "C" std::uint32_t* FUN_00409680()
{
    const int allocator = DAT_01223388;
    std::uint32_t* freeNode = *reinterpret_cast<std::uint32_t**>(allocator + 8);

    if (freeNode != nullptr)
    {
        const std::uint32_t next = *freeNode;
        *reinterpret_cast<int*>(allocator + 0x14) = *reinterpret_cast<int*>(allocator + 0x14) + -1;
        *reinterpret_cast<std::uint32_t*>(allocator + 8) = next;

        if (*reinterpret_cast<std::uint32_t*>(allocator + 0x14) <
            *reinterpret_cast<std::uint32_t*>(allocator + 0x18))
        {
            *reinterpret_cast<std::uint32_t*>(allocator + 0x18) =
                *reinterpret_cast<std::uint32_t*>(allocator + 0x14);
        }

        return freeNode;
    }

    if (*reinterpret_cast<int**>(allocator + 0x1c) != nullptr)
    {
        auto** const object = reinterpret_cast<int**>(allocator + 0x1c);
        auto* const vtable = *reinterpret_cast<std::uint8_t**>(*object);
        const auto method =
            *reinterpret_cast<std::uint32_t* (**)(std::uint32_t, std::uint32_t)>(vtable + 4);

        return method(
            *reinterpret_cast<std::uint32_t*>(allocator + 0xc),
            *reinterpret_cast<std::uint32_t*>(allocator + 0x10));
    }

    return nullptr;
}