// FUNC_NAME: initializeGameSystems
void initializeGameSystems(uint32 param_1)
{
    int iVar1;
    uint32* puVar2;
    uint32 local_c;
    uint32 local_8;
    uint32 local_4;

    // Set global initialization state
    g_gameState = 1; // DAT_01194540
    g_someFlag1 = 0; // _DAT_01194738
    g_someFlag2 = 0; // _DAT_01194740
    g_someFlag3 = 0; // DAT_01194748

    // Allocate and initialize first object (size 12 bytes)
    g_firstObject = (uint32*)allocateMemory(12); // FUN_009c8e50(0xc)
    if (g_firstObject == nullptr) {
        g_firstObject = nullptr;
    } else {
        g_firstObject[0] = 0;
        g_firstObject[1] = 0;
        g_firstObject[2] = 0;
    }

    // Allocate and construct second object (size 24 bytes)
    iVar1 = allocateMemory(24); // FUN_009c8e50(0x18)
    if (iVar1 == 0) {
        g_secondObject = 0;
    } else {
        g_secondObject = constructSecondObject(); // FUN_004e0830
    }

    // Allocate and construct third object (size 24 bytes)
    iVar1 = allocateMemory(24); // FUN_009c8e50(0x18)
    if (iVar1 == 0) {
        g_thirdObject = 0;
    } else {
        g_thirdObject = constructThirdObject(); // FUN_004e0950
    }

    // Allocate main manager object (size 56 bytes)
    puVar2 = (uint32*)allocateMemory(56); // FUN_009c8e50(0x38)
    if (puVar2 != nullptr) {
        puVar2[1] = 1;
        puVar2[2] = 0;
        puVar2[3] = (uint32)&vtable_00e36f70; // PTR_LAB_00e36f70
        g_mainManager = puVar2;
        puVar2[0] = (uint32)&vtable_00e36f5c; // PTR_FUN_00e36f5c
        puVar2[3] = (uint32)&vtable_00e36f6c; // PTR_LAB_00e36f6c
        puVar2[4] = 0;
        puVar2[5] = 0;
        puVar2[6] = 0;
        puVar2[8] = 0;
        puVar2[9] = 0;
        puVar2[10] = 0;
        puVar2[0xb] = 0;
        puVar2[0xc] = 0;
        puVar2[0xd] = 0;
    }
    g_mainManager[0xd] = param_1; // Store parameter at offset 0x34

    // Call sub-initialization on main manager
    subInitMainManager(g_mainManager); // FUN_004dfd70

    // Allocate another object (size 20 bytes)
    iVar1 = allocateMemory(20); // FUN_009c8e50(0x14)
    if (iVar1 != 0) {
        getSomeGlobalPointer(); // FUN_009c8f80
        callAnotherInit(); // FUN_0066cf70
    }

    // Get a global pointer and call a virtual function with large size
    puVar2 = (uint32*)getSomeGlobalPointer(); // FUN_009c8f80
    local_c = 2;
    local_8 = 0x10;
    local_4 = 0;
    iVar1 = (*(code**)*puVar2)(0xa2e00, &local_c); // Virtual call with size 666624
    if (iVar1 != 0) {
        processLargeAllocation(iVar1); // FUN_0051ee80
    }

    // Get global pointer again and allocate another object via virtual call
    puVar2 = (uint32*)getSomeGlobalPointer(); // FUN_009c8f80
    local_c = 0;
    puVar2 = (uint32*)(*(code**)*puVar2)(0xc, &local_c); // Virtual call with size 12
    g_gameState = 3; // DAT_01194540

    if (puVar2 != nullptr) {
        g_lastObject = puVar2;
        puVar2[0] = (uint32)&vtable_00e376b8; // PTR_LAB_00e376b8
        puVar2[1] = 0;
        puVar2[2] = 0;
    }
}