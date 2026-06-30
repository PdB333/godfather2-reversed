void FUN_004042e0(int param_1, float param_2)
{
    int resolved;
    std::uint32_t local_c;
    undefined4* local_10;
    int iVar4;
    int container;
    byte count;
    std::uint32_t uVar6;
    undefined4* puVar5;

    if ((param_1 != 0) && ((resolved = FUN_004025a0(param_1)), resolved != 0)) {
        local_c = 0;

        if (*reinterpret_cast<int*>(resolved + 0xec) != 0) {
            local_10 = reinterpret_cast<undefined4*>(resolved + 0x78);

            do {
                const undefined4 child = *local_10;
                iVar4 = FUN_004025a0(child);

                if (*reinterpret_cast<float*>(iVar4 + 0x4c) != DAT_00e2eff4) {
                    FUN_004042e0(child, *reinterpret_cast<float*>(iVar4 + 0x4c) * param_2);
                }

                local_10 = local_10 + 1;
                local_c = local_c + 1;
            } while (local_c < *reinterpret_cast<std::uint32_t*>(resolved + 0xec));
        }

        FUN_004043f0(param_2);

        container = *reinterpret_cast<int*>(resolved + 0x18);
        if (container != 0) {
            count = *reinterpret_cast<byte*>(container + 9);
            uVar6 = 0;

            if (count != 0) {
                do {
                    puVar5 = reinterpret_cast<undefined4*>(
                        FUN_00405fd0(
                            container,
                            *reinterpret_cast<undefined4*>(
                                *reinterpret_cast<int*>(container + 0x10) +
                                (static_cast<std::uint32_t>(*reinterpret_cast<byte*>(container + 8)) +
                                 (static_cast<std::uint32_t>(*reinterpret_cast<byte*>(container + 10)) & 1) +
                                 uVar6) * 4)));

                    iVar4 = FUN_004059b0(*reinterpret_cast<undefined4*>(*puVar5));
                    if (iVar4 != 0) {
                        FUN_004042e0(iVar4, param_2);
                    }

                    uVar6 = uVar6 + 1;
                } while (uVar6 < count);
            }
        }
    }

    return;
}