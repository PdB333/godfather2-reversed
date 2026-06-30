extern "C" void FUN_0064f620()
{
    if (*reinterpret_cast<int*>(unaff_ESI + 0x1FC) == 0) {
        *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x200) = 0;
        *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x204) = 0;

        void* pvVar1 = reinterpret_cast<void*>(FUN_009c8e80(0x1000));
        *reinterpret_cast<void**>(unaff_ESI + 0x1FC) = pvVar1;
        _memset(pvVar1, 0, 0x1000);

        pvVar1 = reinterpret_cast<void*>(FUN_009c8e80(0xC000));
        if (pvVar1 == nullptr) {
            pvVar1 = nullptr;
        } else {
            _vector_constructor_iterator_(
                pvVar1,
                0x30,
                0x400,
                reinterpret_cast<_func_void_ptr_void_ptr*>(&LAB_0064f350)
            );
        }
        *reinterpret_cast<void**>(unaff_ESI + 0x214) = pvVar1;

        int iVar4 = 0;
        int iVar2 = 0;
        do {
            *reinterpret_cast<int*>(
                reinterpret_cast<int>(*reinterpret_cast<void**>(unaff_ESI + 0x214)) + 0x28 + iVar2
            ) = iVar4;
            iVar2 = iVar2 + 0x30;
            iVar4 = iVar4 + 1;
        } while (iVar2 < 0xC000);

        const std::uint32_t uVar3 = FUN_009c8e80(0x1000);
        *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x218) = uVar3;

        iVar2 = 0;
        do {
            *reinterpret_cast<std::uint32_t*>(iVar2 + *reinterpret_cast<int*>(unaff_ESI + 0x218)) = 0;
            iVar2 = iVar2 + 4;
        } while (iVar2 < 0x1000);
    }
}