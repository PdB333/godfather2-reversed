extern "C" std::uint32_t FUN_0040d330()
{
#if defined(_MSC_VER) && defined(_M_IX86)
    void* teb = reinterpret_cast<void*>(__readfsdword(0x18));
#else
    NT_TIB* tib = reinterpret_cast<NT_TIB*>(NtCurrentTeb());
    void* teb = tib;
#endif

    auto const threadData =
        *reinterpret_cast<std::int32_t**>(reinterpret_cast<std::uintptr_t>(teb) + 0x2c);

    return *reinterpret_cast<std::uint32_t*>(*threadData + 4);
}