extern "C" void __fastcall FUN_00408980(std::uint32_t param_1, const char* param_2)
{
    FUN_00408310(param_1);

    if (param_2 != nullptr && *param_2 != '\0')
    {
        const auto uVar1 = FUN_004dafd0(const_cast<char*>(param_2));
        FUN_00408260(param_1, uVar1);
    }
}