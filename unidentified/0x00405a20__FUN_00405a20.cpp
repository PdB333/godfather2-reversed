extern "C" std::uint32_t FUN_00405a20(int param_1, int param_2)
{
    std::uint32_t* puVar1;
    int iVar2;
    int iVar3;
    std::uint8_t* puVar4;
    int unaff_EDI; // preserved from original context

    std::uint8_t local_c[4];
    int local_8[2];

    // Exact initialization order as in Ghidra
    local_8[0] = param_1 + 0x68;
    puVar1 = *reinterpret_cast<std::uint32_t**>(param_1 + 0x70);
    local_8[1] = 0;
    puVar4 = local_c;
    iVar2 = 0;

    while (true)
    {
        // Exact for-loop semantics preserved
        for (; puVar1 == (std::uint32_t*)0x0; puVar1 = *reinterpret_cast<std::uint32_t**>(*puVar1))
        {
            puVar1 = reinterpret_cast<std::uint32_t*>(puVar4 + 4);
            puVar4 = puVar4 + 4;

            if ((std::uint32_t*)*reinterpret_cast<std::uint32_t*>(puVar1) == (std::uint32_t*)0x0)
            {
                return 0;
            }
        }

        iVar3 = iVar2;

        if ((puVar1[0xb] == static_cast<std::uint32_t>(param_2)) &&
            ((iVar3 = iVar2 + 1), iVar2 == unaff_EDI))
        {
            break;
        }

        puVar1 = *reinterpret_cast<std::uint32_t**>(puVar1);
        iVar2 = iVar3;
    }

    return puVar1[7];
}