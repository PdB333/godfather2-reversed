extern "C" void FUN_00408bb0(std::uint32_t* param_1, std::uint32_t param_2, std::uint32_t param_3, std::uint32_t param_4)
{
    struct LocalState
    {
        std::uint32_t value;
        std::uint32_t forwardedParam;
        std::uint8_t flag;
    };

    LocalState localState{};
    localState.value = *param_1;
    localState.forwardedParam = param_3;
    localState.flag = 0;

    FUN_00408bf0(&localState.value, param_2, param_4);
}