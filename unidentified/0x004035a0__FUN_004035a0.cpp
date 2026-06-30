std::uint8_t __thiscall FUN_004035a0(std::uint32_t thisPtr)
{
    if ((*reinterpret_cast<std::int32_t*>(thisPtr + 0x70) == 0) &&
        (*reinterpret_cast<std::int32_t*>(thisPtr + 0x78) == 0)) {
        return 1;
    }

    return 0;
}