// FUNC_NAME: gameManagerShutdown

int gameManagerShutdown(void* this) {
    int* pData;
    char bCondition;
    int* pSub;

    pData = g_pManager1; // DAT_01223514
    memManagerTick(); // FUN_005dbc10
    bCondition = checkSomething(); // FUN_005f0840
    if (bCondition != '\0') {
        pSub = pData + 2;
        pData[1] = 0; // clear some field
        if (pSub != (int*)0x0) {
            *pSub = 0; // clear at offset +8
            pData[3] = 0; // clear at offset +12
            *(short*)(pData + 4) = 0; // clear at offset +16, 2 bytes
            *(short*)((int)pData + 0x12) = 0; // clear at offset +18
            memManagerTick(pSub, 0); // FUN_005dbc10 with param
            someResetFunc(); // FUN_005f2de0
        }
    }
    if (g_pManager1 != (int*)0x0) {
        (*(void(__thiscall**)(int))(*g_pManager1))(1); // virtual release/dtor
    }
    memManagerTick(); // FUN_005dbc10
    if ((g_pFlag != 0) && (g_pOtherFlag != 0)) { // DAT_011a0ee0, DAT_011a0edc
        someShutdownFunc(); // FUN_005f5910
    }
    anotherShutdownFunc(); // FUN_005f1cc0
    yetAnotherShutdownFunc(); // FUN_005e1e50
    if (g_pManager2 != (int*)0x0) { // DAT_0122350c
        (*(void(__thiscall**)(int))(*g_pManager2))(1); // virtual release
    }
    pData = g_pGlobalStruct; // DAT_012234bc
    pSub = pData + 0x1804 / sizeof(int); // &pData[0x1804/4] = offset 0x1804
    int* pTemp = g_pGlobalStruct;
    if ((int*)(g_pGlobalStruct[0x1804 / 4]) != (int*)0x0) { // field at +0x1804
        pTemp = g_pGlobalStruct + 0x180f / 4; // offset 0x180f
        if (g_pGlobalStruct[0x180f / 4] != 0) { // field at +0x180f
            (*(void(__thiscall**)(int, int))(*(int*)g_pGlobalStruct[0x1804 / 4] + 4))(g_pGlobalStruct[0x180f / 4], 0); // call vtable+4 on object
            *pTemp = 0; // clear field
        }
        (*(void(__thiscall**)(void))(*(int*)*pSub + 0xc))(); // call vtable+12 on object
        pTemp = g_pGlobalStruct;
        *pSub = 0; // clear field at +0x1804
    }
    if (pTemp != (int*)0x0) {
        (*(void(__thiscall**)(int))(*pTemp))(0); // release with flag 0
        if (*(int**)((int)this + 4) != (int*)0x0) {
            (*(void(__thiscall**)(int*, int))(**(int**)((int)this + 4) + 4))(pTemp, 0); // call vtable+4 on something
        }
    }
    someOtherShutdown(); // FUN_005e7320
    if (g_pManager3 != (int*)0x0) { // DAT_01223504
        (*(void(__thiscall**)(int))(*g_pManager3))(1);
    }
    preShutdownFunc(); // FUN_005dc1a0
    if (g_pManager4 != (int*)0x0) { // DAT_01223508
        (*(void(__thiscall**)(int))(*g_pManager4))(1);
    }
    (*(void(__thiscall**)(void))(*g_pManager5 + 8))(); // DAT_01223510, call vtable+8
    if (g_pManager5 != (int*)0x0) {
        (*(void(__thiscall**)(int))(*g_pManager5))(1);
    }
    if (*(int**)((int)this + 4) != (int*)0x0) {
        (*(void(__thiscall**)(void))(**(int**)((int)this + 4) + 0xc))(); // call vtable+12 on object
        *(int*)((int)this + 4) = 0; // clear this->field+4
        return 1;
    }
    return 0;
}