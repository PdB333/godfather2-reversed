extern "C" void FUN_00409d80(std::uint32_t param_1)
{
    if (DAT_0110ae75 != '\0')
    {
        if (param_1 < 5)
        {
            param_1 = 5;
        }

        float value = static_cast<float>(static_cast<int>(param_1));
        DAT_0110ae7c = param_1;

        if (static_cast<int>(param_1) < 0)
        {
            value = value + DAT_00e44578;
        }

        _DAT_012067f8 = value * DAT_01206a30 * DAT_00e2e210;
        return;
    }

    if (5 < param_1)
    {
        float value = static_cast<float>(static_cast<int>(param_1));

        if (static_cast<int>(param_1) < 0)
        {
            value = value + DAT_00e44578;
        }

        _DAT_012067ec = static_cast<std::uint32_t>(
            static_cast<long long>(
                std::round(
                    static_cast<double>(DAT_00e2cd54) +
                    static_cast<double>(value) * static_cast<double>(DAT_01206a30)
                )
            )
        );
        _DAT_012067f8 = value * DAT_01206a30 * DAT_00e2e210;
    }
}