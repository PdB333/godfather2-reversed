extern "C" void __thiscall FUN_004089b0(std::uint32_t param_1, std::int32_t* param_2, char* param_3)
{
    FUN_004086d0(param_2);
    FUN_00408310(param_2);

    if (param_3 != nullptr && *param_3 != '\0')
    {
        const auto uVar1 = FUN_004dafd0(param_3);
        FUN_00408260(param_2, uVar1);

        if (*param_2 != 0)
        {
            FUN_00407e60(param_1, param_2);
        }
    }
}