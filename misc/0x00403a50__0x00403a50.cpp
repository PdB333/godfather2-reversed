int __thiscall FUN_00403a50(
    undefined4 param_1,
    char* param_2,
    undefined4 param_3,
    unsigned int param_4,
    undefined4* param_5,
    int param_6)
{
    undefined4 value;
    int result;
    undefined1* basePath;
    int tempRef;
    undefined4 local_12c;
    undefined4 local_128;
    undefined4 local_124;
    undefined4 local_120;
    undefined1* local_118;
    void (__cdecl* local_10c)(undefined1*);
    char local_108[260];

    if (param_2 == nullptr) {
        return 0;
    }

    if (*param_2 == '\0') {
        return 0;
    }

    FUN_004d3bc0(param_2);
    FUN_004d5900(1);
    FUN_004d57e0();

    tempRef = 0;
    if ((param_4 & 2u) != 0) {
        tempRef = FUN_004040d0(param_1, param_6);
    }

    result = FUN_004057b0(param_1);
    if (result != 0) {
        result = FUN_00403c40(result, param_3, param_6, param_4);
        goto cleanup;
    }

    if (param_6 == 0) {
        basePath = local_118;
        if (local_118 == nullptr) {
            basePath = &DAT_0120546e;
        }

        __snprintf(local_108, 0x100, "%s%s", basePath, &DAT_00e2f0a0);

        local_12c = 0xbadbadba;
        local_128 = 0xbeefbeef;
        local_124 = 0xeac15a55;
        local_120 = 0x91100911;

        basePath = local_118;
        if (local_118 == nullptr) {
            basePath = &DAT_0120546e;
        }

        FUN_004d9a70(basePath);

allocate_default_handle:
        param_5 = (undefined4*)FUN_00401f40(&local_12c);
    } else {
        basePath = local_118;
        if (local_118 == nullptr) {
            basePath = &DAT_0120546e;
        }

        __snprintf(local_108, 0x100, "%s%s%s", param_6, basePath, &DAT_00e2f0a0);

        if (param_5 == nullptr) {
            FUN_00401ea0();

            basePath = local_118;
            if (local_118 == nullptr) {
                basePath = &DAT_0120546e;
            }

            FUN_004d9a70(basePath);
            goto allocate_default_handle;
        }
    }

    value = *param_5;
    result = FUN_00405900(local_108, 0);
    if (result == 0) {
        result = FUN_00404590(param_1, value, local_108, param_3, param_4);
    }

cleanup:
    if ((tempRef != 0) &&
        ((*(short*)(tempRef + 0xe) = *(short*)(tempRef + 0xe) + -1),
         ((*(unsigned short*)(tempRef + 0xe) & 0x7fffu) == 0))) {
        FUN_00404070();
    }

    if (local_118 != nullptr) {
        local_10c(local_118);
    }

    return result;
}