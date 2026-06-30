void FUN_00402a80()
{
    auto* const self = reinterpret_cast<std::uint8_t*>(unaff_ESI);

    *reinterpret_cast<std::uint32_t*>(self + 0x18) = 0;
    *reinterpret_cast<std::int32_t*>(self + 0x24) = -1;
    *reinterpret_cast<std::uint32_t*>(self + 0x60) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x74) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0xEC) = 0;
    *reinterpret_cast<std::uint16_t*>(self + 0x56) = 0xFFFF;

    if (*reinterpret_cast<std::int32_t*>(self + 0x08) != 0) {
        auto fn = *reinterpret_cast<void(**)(int)>(self + 0x14);
        fn(*reinterpret_cast<std::int32_t*>(self + 0x08));
    }

    *reinterpret_cast<std::uint32_t*>(self + 0x08) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x10) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x0C) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x1C) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x20) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x30) = 0;
    *reinterpret_cast<std::int32_t*>(self + 0x28) = -1;
    *reinterpret_cast<std::int32_t*>(self + 0x24) = -1;
    *reinterpret_cast<std::uint32_t*>(self + 0x38) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x3C) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x40) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x44) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x48) = 0;

    const std::uint32_t uVar1 = DAT_00e2b1a4;

    *reinterpret_cast<std::uint16_t*>(self + 0x54) = 0;
    *reinterpret_cast<std::uint32_t*>(self + 0x4C) = uVar1;
    *reinterpret_cast<std::uint32_t*>(self + 0x50) = 0x100;
}