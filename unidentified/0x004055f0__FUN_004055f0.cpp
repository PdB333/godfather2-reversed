struct FUN_004055f0_StackArg
{
    std::uint32_t field_0;
    std::uint32_t field_4;
    std::uint8_t field_8;
};

void __thiscall FUN_004055f0(void* this_)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    if ((*reinterpret_cast<int*>(self + 0x70) == 0) && (*reinterpret_cast<int*>(self + 0x78) == 0)) {
        if ((*reinterpret_cast<char*>(self + 0x88) != '\0') && (2 < *reinterpret_cast<unsigned int*>(self + 0xA0))) {
            *reinterpret_cast<std::uint8_t*>(self + 0x88) = 0;

            FUN_004055f0_StackArg local{};
            local.field_0 = DAT_012067a4;
            local.field_4 = 0;
            local.field_8 = 0;
            FUN_00408a00(&local, 0);
            return;
        }
    }
    else if (*reinterpret_cast<char*>(self + 0x88) == '\0') {
        *reinterpret_cast<std::uint8_t*>(self + 0x88) = 1;
    }

    return;
}