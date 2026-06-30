// Internal implementation that receives the real EAX value explicitly
static void FUN_00408d50_impl(std::uint32_t eax_count, int param_1)
{
    int alloc_result;
    void* storage;

    if (eax_count == 0)
    {
        eax_count = 0x800;
    }

    alloc_result = FUN_009c8e50(0x20);
    if (alloc_result == 0)
    {
        _DAT_0110aeac = 0;
    }
    else
    {
        storage = reinterpret_cast<void*>(FUN_009c8e80(eax_count * 0x18));
        _DAT_0110aeac = FUN_004abe90(storage, eax_count * 0x18, 0x18, 4);
    }

    DAT_012051fc = _DAT_0110aeac;
    *reinterpret_cast<void***>(_DAT_0110aeac + 0x1c) = &PTR_PTR_0110ae9c;

    if (param_1 == 0)
    {
        param_1 = 5000;
    }

    alloc_result = FUN_009c8e50(0x20);
    if (alloc_result == 0)
    {
        DAT_01205200 = 0;
    }
    else
    {
        storage = reinterpret_cast<void*>(FUN_009c8e80(param_1 * 0xc));
        DAT_01205200 = FUN_004abe90(storage, param_1 * 0xc, 0xc, 4);
    }

    _DAT_0110aec0 = DAT_01205200;
    *reinterpret_cast<void***>(DAT_01205200 + 0x1c) = &PTR_PTR_0110aeb0;
}

// Naked wrapper to preserve incoming EAX exactly as in the original binary
extern "C" __declspec(naked) void FUN_00408d50(int param_1)
{
    __asm
    {
        // Stack layout:
        // [esp+4] = param_1
        mov edx, [esp + 4]   // param_1
        push edx             // push param_1
        push eax             // push original EAX (implicit argument)
        call FUN_00408d50_impl
        add esp, 8
        ret 4
    }
}