extern "C" void FUN_00408e80(std::uint32_t eax_count, int param_1, int param_2)
{
    int alloc_result;
    void* storage;

    if (eax_count == 0)
    {
        eax_count = 15000;
    }

    alloc_result = FUN_009c8e50(0x20);
    if (alloc_result == 0)
    {
        _DAT_0110aed4 = 0;
    }
    else
    {
        storage = reinterpret_cast<void*>(FUN_009c8e80(eax_count << 4));
        _DAT_0110aed4 = FUN_004abe90(storage, eax_count << 4, 0x10, 4);
    }

    DAT_01223384 = _DAT_0110aed4;
    *reinterpret_cast<void***>(_DAT_0110aed4 + 0x1c) = &PTR_PTR_0110aec4;

    if (param_1 == 0)
    {
        param_1 = 500;
    }

    alloc_result = FUN_009c8e50(0x20);
    if (alloc_result == 0)
    {
        _DAT_0110aee8 = 0;
    }
    else
    {
        storage = reinterpret_cast<void*>(FUN_009c8e80(param_1 << 7));
        _DAT_0110aee8 = FUN_004abe90(storage, param_1 << 7, 0x80, 4);
    }

    DAT_01223388 = _DAT_0110aee8;
    *reinterpret_cast<void***>(_DAT_0110aee8 + 0x1c) = &PTR_PTR_0110aed8;

    if (param_2 == 0)
    {
        param_2 = 8;
    }

    alloc_result = FUN_009c8e50(0x20);
    if (alloc_result == 0)
    {
        DAT_0122338c = 0;
    }
    else
    {
        storage = reinterpret_cast<void*>(FUN_009c8e80(param_2 << 10));
        DAT_0122338c = FUN_004abe90(storage, param_2 << 10, 0x400, 4);
    }

    _DAT_0110aefc = DAT_0122338c;
    *reinterpret_cast<void***>(DAT_0122338c + 0x1c) = &PTR_PTR_0110aeec;
}