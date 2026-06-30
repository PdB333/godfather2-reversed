extern "C" void __thiscall FUN_00454770(void* this_, int* param_2)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    void* localObjectA;
    void* localObjectB;

    {
        using GetObjectFn = void* (__thiscall*)(void*);
        auto* const vtable = *reinterpret_cast<void***>(param_2);
        auto* const fn = reinterpret_cast<GetObjectFn>(vtable[1]); // +0x04
        localObjectA = fn(&localObjectA);
    }

    const std::uint32_t valueAtPlus4 =
        *reinterpret_cast<std::uint32_t*>(static_cast<std::uint8_t*>(localObjectA) + 4);

    {
        using GetObjectFn = void* (__thiscall*)(void*);
        auto* const vtable = *reinterpret_cast<void***>(param_2);
        auto* const fn = reinterpret_cast<GetObjectFn>(vtable[1]); // +0x04
        localObjectB = fn(&localObjectB);
    }

    const std::uint32_t valueAtPlus0 =
        *reinterpret_cast<std::uint32_t*>(localObjectB);

    const std::uint32_t ctorArg =
        *reinterpret_cast<std::uint32_t*>(self + 0x5c);

    int object = FUN_009c8e50(0x38);
    if (object == 0) {
        object = 0;
    } else {
        object = FUN_00453440(ctorArg);
    }

    *reinterpret_cast<std::uint32_t*>(object + 0x30) = valueAtPlus0;
    *reinterpret_cast<std::uint32_t*>(object + 0x34) = valueAtPlus4;

    FUN_0064d980();
}