void FUN_00402e90(undefined4 param_1, undefined4 param_2, char param_3)
{
    char cVar1;
    std::uint32_t uVar2;
    char* pcVar3;
    char* pcVar4;
    char* local_118 = nullptr;
    std::uint32_t local_114 = 0;
    void (*local_10c)(char*) = nullptr;
    char local_108[260];

    if (param_3 == '\0') {
        FUN_00401aa0(0x100);
    }
    else {
        FUN_004d3bc0(param_2, &local_118, &local_114, &local_10c);

        if (local_118 == nullptr) {
            pcVar3 = &DAT_0120546e;
        }
        else {
            uVar2 = 0;
            pcVar3 = local_118;
            if (local_114 != 0) {
                do {
                    if (local_118[uVar2] == '/') {
                        local_118[uVar2] = '\\';
                    }
                    uVar2 = uVar2 + 1;
                } while (uVar2 < local_114);
            }
        }

        pcVar4 = local_108;
        do {
            cVar1 = *pcVar3;
            *pcVar4 = cVar1;
            pcVar3 = pcVar3 + 1;
            pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');

        if (local_118 != nullptr) {
            local_10c(local_118);
            FUN_004d3d90(local_108);
            return;
        }
    }

    FUN_004d3d90(local_108);
    return;
}