extern "C" void FUN_0040cfc0()
{
    struct LocalParam
    {
        std::uint32_t value;
        std::uint32_t zeroDword;
        std::uint8_t zeroByte;
    };

    LocalParam local{};
    local.value = DAT_01206940;
    local.zeroDword = 0;
    local.zeroByte = 0;

    FUN_00408a00(&local.value, 0);
}