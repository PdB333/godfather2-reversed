extern "C" void __fastcall FUN_004083d0(std::uint32_t* const param_1)
{
    struct LocalCleanupContext {
        std::uint32_t value;
        std::uint32_t* self;
        std::uint8_t state;
    };

    *param_1 = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f19c);

    LocalCleanupContext localContext{};
    localContext.value = DAT_012067cc;
    localContext.state = 0;
    localContext.self = param_1;

    FUN_00408a00(&localContext.value, 0);
    FUN_004086d0(&DAT_012067d4);
    FUN_004086d0(&DAT_012067c4);

    const std::uint32_t resourceHandle = param_1[2];

    if ((((std::uint32_t)param_1[1] >> 2) & 1U) == 0) {
        if (resourceHandle != 0) {
            FUN_004abf50(resourceHandle);
        }
    }
    else if ((((std::uint32_t)param_1[1] >> 3) & 1U) == 0) {
        if (resourceHandle != 0) {
            FUN_004abf50(resourceHandle);
            return;
        }
    }
    else if (resourceHandle != 0) {
        FUN_004abf50(resourceHandle);
        return;
    }

    return;
}