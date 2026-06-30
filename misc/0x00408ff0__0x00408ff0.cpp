extern "C" void FUN_00408ff0(std::uint32_t eax_count)
{
    int alloc_result;
    void* storage;

    if (eax_count == 0)
    {
        eax_count = 0x200;
    }

    alloc_result = FUN_009c8e50(0x20);
    if (alloc_result != 0)
    {
        storage = reinterpret_cast<void*>(FUN_009c8e80(eax_count * 0x18));
        DAT_01205204 = FUN_004abe90(storage, eax_count * 0x18, 0x18, 4);
        _DAT_0110af10 = DAT_01205204;
        *reinterpret_cast<void***>(DAT_01205204 + 0x1c) = &PTR_PTR_0110af00;
        return;
    }

    _DAT_0110af10 = 0;
    ppuRam0000001c = &PTR_PTR_0110af00;
    DAT_01205204 = 0;
    return;
}