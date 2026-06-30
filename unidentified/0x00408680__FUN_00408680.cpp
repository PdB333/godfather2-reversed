extern "C" void __fastcall FUN_00408680(std::int32_t* const param_1)
{
    if (*param_1 != 0) {
        if (FUN_00402080(param_1) == '\0') {
            *reinterpret_cast<short*>(param_1 + 1) = static_cast<short>(param_1[1]) + 1;
            FUN_004084d0(reinterpret_cast<std::uint32_t*>(param_1), 0x8000);
        }
    }
}