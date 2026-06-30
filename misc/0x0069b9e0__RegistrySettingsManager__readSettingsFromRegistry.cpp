// FUNC_NAME: RegistrySettingsManager::readSettingsFromRegistry
int RegistrySettingsManager::readSettingsFromRegistry(void* param1, void* param2, int param3)
{
    int* puVar1;
    int iVar2;
    void* uVar3;
    int iVar4;
    unsigned int uVar5;
    int iVar6;
    int local_20[3]; // buffer for registry value data (e.g., REG_BINARY)
    void* local_14;  // function pointer to cleanup (e.g., RegCloseKey)
    int local_10[3]; // another buffer for registry value data
    void* local_4;   // function pointer to cleanup

    iVar4 = param3;
    iVar6 = (int)g_registryEnd - (int)g_registryBase; // DAT_01129f90 - 0x1129f8c
    uVar5 = 0;
    if (param3 == 0) {
        // First call: allocate buffer and read from base software key
        iVar4 = FUN_009c8e50(0x3c); // malloc(60)
        if (iVar4 == 0) {
            param3 = 0;
        }
        else {
            uVar3 = FUN_004dbef0(L"SOFTWARE\\"); // RegCreateKeyExW or RegOpenKeyExW
            FUN_004dba00(L"SOFTWARE\\", uVar3); // RegSetValueExW? Actually might be something else
            uVar5 = 4;
            param3 = FUN_0069ad30(&g_registryBase, param2, param1, local_10); // read registry value
        }
        if (g_registryEnd < g_registryCapacity) { // DAT_01129f90 < 0x1129f94
            puVar1 = g_registryEnd + 1;
            if (g_registryEnd != (int*)0x0) {
                *g_registryEnd = param3;
                g_registryEnd = puVar1;
                puVar1 = g_registryEnd;
            }
        }
        else {
            FUN_0069ab10(g_registryEnd, &param3); // vector push_back
            puVar1 = g_registryEnd;
        }
    }
    else {
        // Subsequent call: use param3 as subkey pointer
        iVar2 = FUN_009c8e50(0x3c); // malloc(60)
        if (iVar2 == 0) {
            param3 = 0;
        }
        else {
            FUN_004dba80(&g_someKey, 0); // RegCloseKey? or set value to 0
            uVar3 = FUN_004dbef0(iVar4); // RegOpenKeyExW on subkey
            FUN_004dba00(iVar4, uVar3); // RegSetValueExW? 
            uVar5 = 3;
            param3 = FUN_0069ad30(local_20, param2, param1, local_10); // read registry value
        }
        if (g_registryEnd < g_registryCapacity) {
            puVar1 = g_registryEnd + 1;
            if (g_registryEnd != (int*)0x0) {
                *g_registryEnd = param3;
                g_registryEnd = puVar1;
                puVar1 = g_registryEnd;
            }
        }
        else {
            FUN_0069ab10(g_registryEnd, &param3);
            puVar1 = g_registryEnd;
        }
        g_registryEnd = puVar1;
        // Cleanup if allocation succeeded and buffer was used
        if ((iVar2 != 0) && (uVar5 = uVar5 & 0xfffffffd, local_20[0] != 0)) {
            ((void (*)(int))local_14)(local_20[0]); // call cleanup function (e.g., RegCloseKey)
        }
        uVar5 = uVar5 & 1;
        puVar1 = g_registryEnd;
    }
    g_registryEnd = puVar1;
    // Final cleanup if needed
    if ((uVar5 != 0) && (local_10[0] != 0)) {
        ((void (*)(int))local_4)(local_10[0]); // call cleanup function
    }
    // Return number of entries in registry list (difference/4)
    return iVar6 >> 2;
}