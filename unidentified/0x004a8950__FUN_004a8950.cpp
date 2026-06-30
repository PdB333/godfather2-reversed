extern "C" std::uint8_t __thiscall FUN_004a8950(void* this_, std::uint32_t param_2)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    std::uint8_t result = 1;

    auto* const handler = *reinterpret_cast<void**>(self + 0x40);
    const std::uint8_t flags = *reinterpret_cast<std::uint8_t*>(self + 0x3c);

    if ((handler != nullptr) && ((flags & 1) == 0)) {
        using InvokeFn = std::uint8_t (__thiscall*)(void*, std::uint32_t);
        auto* const vtable = *reinterpret_cast<void***>(handler);
        auto* const invoke = reinterpret_cast<InvokeFn>(vtable[3]); // +0x0c

        result = invoke(handler, param_2);
        FUN_00454810(self + 0x48);
    }

    return result;
}