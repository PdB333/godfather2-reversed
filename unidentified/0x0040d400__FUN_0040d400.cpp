extern "C" void FUN_0040d400(int param_1)
{
#if defined(_MSC_VER) && defined(_M_IX86)
    void* teb = reinterpret_cast<void*>(__readfsdword(0x18));
#else
    NT_TIB* tib = reinterpret_cast<NT_TIB*>(NtCurrentTeb());
    void* teb = tib;
#endif

    auto* const threadData =
        *reinterpret_cast<std::int32_t**>(reinterpret_cast<std::uintptr_t>(teb) + 0x2c);

    const std::uintptr_t base =
        reinterpret_cast<std::uintptr_t>(*threadData);

    *reinterpret_cast<std::int32_t*>(base + 4) = param_1;

    if (*reinterpret_cast<std::int32_t*>(base + 0x34) == 0) {
        auto* const stackTop = reinterpret_cast<std::int32_t*>(DAT_01206880 + 0x14);

        *reinterpret_cast<void**>(*stackTop) =
            const_cast<void*>(reinterpret_cast<void const*>(&PTR_LAB_0110af8c));

        *stackTop = *stackTop + 4;
        *reinterpret_cast<std::int32_t*>(*stackTop) = param_1;
        *stackTop = *stackTop + 4;
        return;
    }

    if (param_1 != 0) {
        FUN_00422a40(DAT_012058a4, DAT_012058a8, 0, 0);
    }
}