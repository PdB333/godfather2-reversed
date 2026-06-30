// FUNC_NAME: GodfatherGameManager::shutdown
void __thiscall GodfatherGameManager::shutdown(int thisPtr)
{
    // Initialize cleanup sequence - calls subsystem destructors
    // Each subsystem cleanup function is called in order
    cleanupSubsystem1();  // 0x008b82d0
    cleanupSubsystem2();  // 0x006cc350
    cleanupSubsystem3();  // 0x009cfa50

    // Destroy global singleton objects via vtable dispatch (argument 1 = delete flag)
    if (g_pSingletonA) {
        ((void (__fastcall*)(int))*g_pSingletonA)(1);
    }
    if (g_pSingletonB) {
        ((void (__fastcall*)(int))*g_pSingletonB)(1);
    }
    if (g_pSingletonC) {
        ((void (__fastcall*)(int))*g_pSingletonC)(1);
    }
    if (g_pSingletonD) {
        ((void (__fastcall*)(int))*g_pSingletonD)(1);
    }
    if (g_pSingletonE) {
        ((void (__fastcall*)(int))*g_pSingletonE)(1);
    }
    if (g_pSingletonF) {
        ((void (__fastcall*)(int))*g_pSingletonF)(1);
    }
    if (g_pSingletonG) {
        ((void (__fastcall*)(int))*g_pSingletonG)(1);
    }

    cleanupSubsystem4();  // 0x006938a0
    cleanupSubsystem5();  // 0x00693840
    cleanupSubsystem6(0); // 0x009202e0
    cleanupSubsystem7();  // 0x00868a30

    if (g_pSingletonH) {
        ((void (__fastcall*)(int))*g_pSingletonH)(1);
    }
    if (g_pSingletonI) {
        ((void (__fastcall*)(int))*g_pSingletonI)(1);
    }
    if (g_pSingletonJ) {
        ((void (__fastcall*)(int))*g_pSingletonJ)(1);
    }
    if (g_pSingletonK) {
        ((void (__fastcall*)(int))*g_pSingletonK)(1);
    }
    if (g_pSingletonL) {
        ((void (__fastcall*)(int))*g_pSingletonL)(1);
    }
    if (g_pSingletonM) {
        ((void (__fastcall*)(int))*g_pSingletonM)(1);
    }
    if (g_pSingletonN) {
        ((void (__fastcall*)(int))*g_pSingletonN)(1);
    }
    if (g_pSingletonO) {
        ((void (__fastcall*)(int))*g_pSingletonO)(1);
    }

    cleanupSubsystem8();   // 0x006a61d0
    cleanupSubsystem9();   // 0x006a80b0

    if (g_pSingletonP) {
        ((void (__fastcall*)(int))*g_pSingletonP)(1);
    }
    if (g_pSingletonQ) {
        ((void (__fastcall*)(int))*g_pSingletonQ)(1);
    }
    if (g_pSingletonR) {
        ((void (__fastcall*)(int))*g_pSingletonR)(1);
    }
    if (g_pSingletonS) {
        ((void (__fastcall*)(int))*g_pSingletonS)(1);
    }
    if (g_pSingletonT) {
        ((void (__fastcall*)(int))*g_pSingletonT)(1);
    }

    cleanupSubsystem10(); // 0x00447fe0
    cleanupSubsystem11(); // 0x00442320
    cleanupSubsystem12(); // 0x00444d90
    cleanupSubsystem13(); // 0x009cb680
    cleanupSubsystem14(); // 0x0082a2c0

    // Destroy subobject at offset 0x4d30 (if exists)
    {
        int *pSubObj = *(int *)(thisPtr + 0x4d30);
        if ((pSubObj != 0) && (pSubObj != (int *)-0xc)) {
            ((void (__fastcall*)(int))*pSubObj)(1);
        }
    }

    cleanupSubsystem15(); // 0x00435b20

    if (g_pSingletonU) {
        ((void (__fastcall*)(int))*g_pSingletonU)(1);
    }

    cleanupSubsystem16(); // 0x00439f30
    cleanupSubsystem17(); // 0x00424950

    if (g_pSingletonV) {
        ((void (__fastcall*)(int))*g_pSingletonV)(1);
    }

    // Call a member function via vtable at global g_someTable
    ((void (__fastcall*)())*(g_someTable + 4))();

    // Update vtable pointer for subobject at offset 0x14 from DAT_01206880
    int *pVtableSlot = (int *)(DAT_01206880 + 0x14);
    *(int *)pVtableSlot = (int)&s_vtableSubObject_00e5011c;
    *pVtableSlot = *pVtableSlot + 4; // Adjust vtable pointer?

    // Execute four cycles of cleanup pair
    for (int i = 0; i < 4; i++) {
        cleanupPairPart1(0); // 0x0068bcd0
        cleanupPairPart2(0); // 0x0068baf0
    }

    if (g_pSingletonW) {
        ((void (__fastcall*)(int))*g_pSingletonW)(1);
    }
    if (g_pSingletonX) {
        ((void (__fastcall*)(int))*g_pSingletonX)(1);
    }
    if (g_pSingletonY) {
        ((void (__fastcall*)(int))*g_pSingletonY)(1);
    }
    if (g_pSingletonZ) {
        ((void (__fastcall*)(int))*g_pSingletonZ)(1);
    }
    // ... additional singleton checks (abbreviated for clarity)
    // (all similar pattern)

    // Destroy subobject at offset 0x7e4
    if (*(int *)(thisPtr + 0x7e4)) {
        ((void (__fastcall*)(int))**(int **)(thisPtr + 0x7e4))(1);
    }

    if (g_pSingletonAA) {
        ((void (__fastcall*)(int))*g_pSingletonAA)(1);
    }

    cleanupSubsystem18(); // 0x006fd400

    // More singleton checks...
    if (g_pSingletonAB) {
        ((void (__fastcall*)(int))*g_pSingletonAB)(1);
    }
    // ... continue pattern

    cleanupSubsystem19(); // 0x00621390
    cleanupSubsystem20(); // 0x008c71a0
    cleanupSubsystem21(); // 0x00782e50
    cleanupSubsystem22(); // 0x007864e0
    cleanupSubsystem23(); // 0x0043bee0

    // Call cleanupSubsystem24 four times
    for (int j = 0; j < 4; j++) cleanupSubsystem24(); // 0x0083e830

    cleanupSubsystem25(); // 0x00812960
    cleanupSubsystem26(); // 0x0053ee80
    cleanupSubsystem27(); // 0x0043e860
    cleanupSubsystem28(); // 0x006bc620

    if (g_pSingletonAC) {
        ((void (__fastcall*)(int))*g_pSingletonAC)(1);
    }

    cleanupSubsystem29(); // 0x0040a7d0

    if (g_pSingletonAD) {
        ((void (__fastcall*)(int))*g_pSingletonAD)(1);
    }

    // Destroy subobject at offset 0x83c
    if (*(int *)(thisPtr + 0x83c)) {
        ((void (__fastcall*)(int))**(int **)(thisPtr + 0x83c))(1);
    }

    cleanupSubsystem30(); // 0x008e9c30

    if (g_pSingletonAE) {
        ((void (__fastcall*)(int))*g_pSingletonAE)(1);
    }
    if (g_pSingletonAF) {
        ((void (__fastcall*)(int))*g_pSingletonAF)(1);
    }

    cleanupSubsystem31(); // 0x0071c9a0

    if (g_pSingletonAG) {
        ((void (__fastcall*)(int))*g_pSingletonAG)(1);
    }
    if (g_pSingletonAH) {
        ((void (__fastcall*)(int))*g_pSingletonAH)(1);
    }

    cleanupSubsystem32(); // 0x004062c0
    cleanupSubsystem33(); // 0x00443100
    cleanupSubsystem34(); // 0x00602e30

    // Destroy subobject at offset 0x4d30 via helper
    if (*(int *)(thisPtr + 0x4d30) != 0) {
        destroySubObjectHelper(thisPtr + 0x4d30); // 0x004daf90
    }

    cleanupSubsystem35(); // 0x00709f10
    cleanupSubsystem36(); // 0x009b8780
    cleanupSubsystem37(); // 0x007875e0
    cleanupSubsystem38(); // 0x008e6120
    cleanupSubsystem39(); // 0x00729560
    cleanupSubsystem40(); // 0x0077b650
    cleanupSubsystem41(); // 0x007f2470
    cleanupSubsystem42(); // 0x0084b350
    cleanupSubsystem43(); // 0x0084acb0
    cleanupSubsystem44(); // 0x00849980
    cleanupSubsystem45(); // 0x0078e300
    cleanupSubsystem46(); // 0x00792c50
    cleanupSubsystem47(); // 0x008f84b0
    cleanupSubsystem48(); // 0x0083ade0
    cleanupSubsystem49(); // 0x0083a9d0
    cleanupSubsystem50(); // 0x0083b160
    cleanupSubsystem51(); // 0x0071ea00
    cleanupSubsystem52(); // 0x0043ff10
    cleanupSubsystem53(); // 0x005f7620
    cleanupSubsystem54(); // 0x005facc0
    cleanupSubsystem55(); // 0x006ac960
    cleanupSubsystem56(); // 0x0083a710
    cleanupSubsystem57(); // 0x006b0580
    cleanupSubsystem58(); // 0x00826780
    cleanupSubsystem59(); // 0x007edb30
    cleanupSubsystem60(); // 0x004403f0
    cleanupSubsystem61(); // 0x00441aa0

    // Set vtable pointers for multiple subobjects and call vtable helper
    // Subobject 1 at offset 0x240
    {
        int *pvtableSlot;
        if (thisPtr == -0x220) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x240);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580d8;
        g_someFlag1 = 0;
        vtableDestructorHelper(); // 0x007edfb0
    }

    // Subobject 2 at offset 0x21c
    {
        int *pvtableSlot;
        if (thisPtr == -0x1fc) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x21c);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580d0;
        g_someFlag2 = 0;
        vtableDestructorHelper();
    }

    // Subobject 3 at offset 0x1f8
    {
        int *pvtableSlot;
        if (thisPtr == -0x1d8) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x1f8);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580cc;
        g_someFlag3 = 0;
        vtableDestructorHelper();
    }

    // Subobject 4 at offset 0x1d4
    {
        int *pvtableSlot;
        if (thisPtr == -0x1b4) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x1d4);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580e4;
        g_someFlag4 = 0;
        vtableDestructorHelper();
    }

    // Subobject 5 at offset 0x1b0
    {
        int *pvtableSlot;
        if (thisPtr == -400) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x1b0);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580fc;
        g_someFlag5 = 0;
        vtableDestructorHelper();
    }

    // Subobject 6 at offset 0x18c
    {
        int *pvtableSlot;
        if (thisPtr == -0x16c) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x18c);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580e8;
        g_someFlag6 = 0;
        vtableDestructorHelper();
    }

    // Subobject 7 at offset 0x168
    {
        int *pvtableSlot;
        if (thisPtr == -0x148) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x168);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580e0;
        g_someFlag7 = 0;
        vtableDestructorHelper();
    }

    // Subobject 8 at offset 0x144
    {
        int *pvtableSlot;
        if (thisPtr == -0x124) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x144);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580dc;
        g_someFlag8 = 0;
        vtableDestructorHelper();
    }

    // Subobject 9 at offset 0x120
    {
        int *pvtableSlot;
        if (thisPtr == -0x100) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0x120);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580c8;
        g_someFlag9 = 0;
        vtableDestructorHelper();
    }

    // Subobject 10 at offset 0xfc
    {
        int *pvtableSlot;
        if (thisPtr == -0xdc) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0xfc);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580ec;
        g_someFlag10 = 0;
        vtableDestructorHelper();
    }

    // Subobject 11 at offset 0xd8
    {
        int *pvtableSlot;
        if (thisPtr == -0xb8) {
            pvtableSlot = 0;
        } else {
            pvtableSlot = (int *)(thisPtr + 0xd8);
        }
        *pvtableSlot = (int)&s_vtableSubObj_00d580f8;
        g_someFlag11 = 0;
        vtableDestructorHelper();
    }

    // Final cleanup calls
    finalCleanup1(); // 0x0043c050
    finalCleanup2(); // 0x00814090
    finalCleanup3(); // 0x00893d60
    finalCleanup4(); // 0x008ffb00
    finalCleanup5(); // 0x00442030

    return;
}