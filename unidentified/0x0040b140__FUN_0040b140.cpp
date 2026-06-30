extern "C" void __cdecl FUN_0040b140(std::uint32_t param_1, std::uint32_t /*param_2*/, float param_3, float param_4)
{
    const float area = param_4 * param_3;

    if (DAT_00e2e210 < area) {
        float colorG = static_cast<float>((param_1 >> 8) & 0xffU) * DAT_00e44640;
        float colorB = static_cast<float>((param_1 >> 16) & 0xffU) * DAT_00e44640;
        float colorA = static_cast<float>(param_1 >> 24) * DAT_00e44640;

        std::uint32_t zero0 = 0;
        std::uint32_t zero1 = 0;
        std::uint32_t zero2 = 0;
        std::uint32_t zero3 = 0;

        std::uint32_t value0 = DAT_00e2b1a4;
        std::uint32_t value1 = DAT_00e2b1a4;
        std::uint32_t value2 = DAT_00e2b1a4;
        std::uint32_t value3 = DAT_00e2b1a4;

        FUN_005149c0(
            *reinterpret_cast<std::uint32_t*>(**reinterpret_cast<std::int32_t**>(__readfsdword(0x2c) + 4)),
            &colorG,
            &value0,
            &value0,
            param_4 * DAT_00e44634,
            0);
    }
}