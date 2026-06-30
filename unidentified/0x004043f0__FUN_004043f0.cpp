void FUN_004043f0(float param_1)
{
    void** local_48 = &PTR_DAT_00e2f0c4;
    int local_8 = 0;
    undefined4 local_4 = 1;
    float local_50 = 0.0f;
    int aiStack_44[15];

    const int resolved = FUN_00405720(*reinterpret_cast<undefined4*>(unaff_EDI + 0x2c), 0);
    if (resolved != 0) {
        aiStack_44[local_8] = resolved;
        local_8 = local_8 + 1;
    }

LAB_00404440:
    do {
        while (true) {
            if (local_8 == 0) {
                return;
            }

            std::uint32_t uVar2 =
                FUN_004059b0(**reinterpret_cast<undefined4**>(aiStack_44[local_8 - 1]));

            std::uint32_t* puVar3 =
                *reinterpret_cast<std::uint32_t**>(
                    *reinterpret_cast<int*>(unaff_ESI + 0x50) +
                    (uVar2 % *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x54)) * 4);

            if (puVar3 == nullptr) {
                break;
            }

            do {
                if (*puVar3 == uVar2) {
                    if ((puVar3 == nullptr) || (puVar3[1] == 0) ||
                        (*reinterpret_cast<int*>(puVar3[1] + 0x24) != 0)) {
                        goto LAB_0040451a;
                    }

                    const float fVar4 = local_50 + param_1;
                    puVar3 =
                        *reinterpret_cast<std::uint32_t**>(
                            *reinterpret_cast<int*>(unaff_ESI + 0x50) +
                            (uVar2 % *reinterpret_cast<std::uint32_t*>(unaff_ESI + 0x54)) * 4);

                    if (puVar3 == nullptr) {
                        goto LAB_0040451a;
                    }

                    goto LAB_004044c6;
                }

                puVar3 = reinterpret_cast<std::uint32_t*>(puVar3[2]);
            } while (puVar3 != nullptr);

            reinterpret_cast<void (*)()>(local_48[1])();
        }

LAB_0040451a:
        reinterpret_cast<void (*)()>(local_48[1])();
    } while (true);

    while ((puVar3 = reinterpret_cast<std::uint32_t*>(puVar3[2])) != nullptr) {
LAB_004044c6:
        if (*puVar3 == uVar2) {
            if ((puVar3 != nullptr) &&
                ((uVar2 = puVar3[1]) != 0) &&
                ((uVar2 == static_cast<std::uint32_t>(unaff_EDI)) ||
                 ((*reinterpret_cast<float*>(uVar2 + 0x48) <= fVar4) &&
                  (fVar4 != *reinterpret_cast<float*>(uVar2 + 0x48))))) {
                FUN_004047c0(uVar2, fVar4);
                local_50 = local_50 + DAT_00e2b1a4;
            }

            goto LAB_0040451a;
        }
    }

    reinterpret_cast<void (*)()>(local_48[1])();
    goto LAB_00404440;
}