extern "C" void __fastcall FUN_00452d80(int* param_1)
{
    if (param_1 != nullptr) {
        using Fn = void (__fastcall*)(int);
        auto* const vtable = *reinterpret_cast<void***>(param_1);
        auto* const fn = reinterpret_cast<Fn>(vtable[1]); // +0x4
        fn(1);
    }
}