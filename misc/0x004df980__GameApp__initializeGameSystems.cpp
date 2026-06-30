// FUNC_NAME: GameApp::initializeGameSystems
void GameApp::initializeGameSystems(int param_1)
{
    int* pAlloc;
    int* pResult;
    int local_10[3]; // {2, 0x10, 0} used for a call

    g_systemState = 1;                     // DAT_01194540 - global init state
    _DAT_01194738 = 0;
    _DAT_01194740 = 0;
    _DAT_01194748 = 0;

    // Allocate 12 bytes for a small object, zero it
    g_ptr_012054c0 = (int*)FUN_009c8e50(0xc);  // DAT_012054c0
    if (g_ptr_012054c0 != (int*)0x0) {
        g_ptr_012054c0[0] = 0;
        g_ptr_012054c0[1] = 0;
        g_ptr_012054c0[2] = 0;
    }

    // Allocate 0x18 bytes and construct object (likely a sound manager or input)
    pAlloc = (int*)FUN_009c8e50(0x18);
    if (pAlloc == 0) {
        g_ptr_012054c4 = 0;                // DAT_012054c4
    } else {
        g_ptr_012054c4 = FUN_004e0830();   // constructor returns pointer
    }

    // Allocate another 0x18 and construct different object
    pAlloc = (int*)FUN_009c8e50(0x18);
    if (pAlloc == 0) {
        g_ptr_012054c8 = 0;                // DAT_012054c8
    } else {
        g_ptr_012054c8 = FUN_004e0950();
    }

    // Allocate 0x38 bytes for a more complex object (likely the engine core)
    int* pEngine = (int*)FUN_009c8e50(0x38);
    if (pEngine != (int*)0x0) {
        pEngine[1] = 1;
        pEngine[2] = 0;
        pEngine[3] = (int)&PTR_LAB_00e36f70;  // vtable+offset?
        g_ptr_012234c4 = pEngine;              // DAT_012234c4
        pEngine[0] = (int)&PTR_FUN_00e36f5c;  // vtable pointer
        pEngine[3] = (int)&PTR_LAB_00e36f6c;  // another vtable entry
        pEngine[4] = 0;
        pEngine[5] = 0;
        pEngine[6] = 0;
        pEngine[8] = 0;
        pEngine[9] = 0;
        pEngine[10] = 0;
        pEngine[0xb] = 0;
        pEngine[0xc] = 0;
        pEngine[0xd] = 0;
    }

    // Store the parameter (probably a window handle or instance)
    g_ptr_012234c4[0xd] = param_1;    // offset +0x34

    // Call a setup function on the engine object
    FUN_004dfd70(g_ptr_012234c4);

    // Allocate 0x14 bytes and call some initialization
    pAlloc = (int*)FUN_009c8e50(0x14);
    if (pAlloc != 0) {
        pResult = (int*)FUN_009c8f80();  // singleton getter
        FUN_0066cf70();                  // another init
    }

    // Get singleton again and call a method with a magic constant
    pResult = (int*)FUN_009c8f80();
    local_10[0] = 2;
    local_10[1] = 0x10;
    local_10[2] = 0;
    int iVar1 = (*(code**)*pResult)(0xa2e00, &local_10);  // method call (vtable)
    if (iVar1 != 0) {
        FUN_0051ee80(iVar1);
    }

    // Another singleton call with a different parameter
    pResult = (int*)FUN_009c8f80();
    local_10[0] = 0;   // reset local_c
    int* pNewObj = (int*)(*(code**)*pResult)(0xc, &local_10[0]);  // method call with size 0xc
    g_systemState = 3;                      // state -> 3

    // Allocate another 12-byte object for final step
    if (pNewObj != (int*)0x0) {
        g_ptr_012234c8 = pNewObj;            // DAT_012234c8
        pNewObj[0] = (int)&PTR_LAB_00e376b8; // vtable
        pNewObj[1] = 0;
        pNewObj[2] = 0;
    }
}