void __thiscall FUN_004035f0(std::uint32_t thisPtr)
{
    const auto object = FUN_004025a0(thisPtr);

    if ((object != 0) && (*reinterpret_cast<std::int16_t*>(object + 0x56) != static_cast<std::int16_t>(-1))) {
        FUN_004029a0(reinterpret_cast<std::int16_t*>(object + 0x56));
    }
}