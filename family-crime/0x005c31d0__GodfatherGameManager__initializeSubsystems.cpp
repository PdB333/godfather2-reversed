// FUNC_NAME: GodfatherGameManager::initializeSubsystems
void GodfatherGameManager::initializeSubsystems(void)
{
    int iVar1;
    undefined4 *puVar2;
    int iVar3;
    undefined4 uVar4;

    // Get singleton instance pointer (global)
    iVar1 = DAT_01205664;

    // Initialize existing members at offsets +0x18, +0x68, +0x6c
    registerObject(iVar1 + 0x18);
    registerObject(iVar1 + 0x68);
    registerObject(iVar1 + 0x6c);

    // Allocate subsystem A (4 bytes, vtable 0x00e3e9c8) at +0xac
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e9c8; // vtable pointer
    }
    *(undefined4 **)(iVar1 + 0xac) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem B (4 bytes, vtable 0x00e3e8e8) at +0x88
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e8e8;
    }
    *(undefined4 **)(iVar1 + 0x88) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem C (4 bytes, vtable 0x00e3e908) at +0x8c
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e908;
    }
    *(undefined4 **)(iVar1 + 0x8c) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem D (8 bytes, vtable 0x00e3ec6c) at +0xb8
    puVar2 = (undefined4 *)allocateMemory(8, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3ec6c;
        puVar2[1] = DAT_01205210; // some global data
    }
    *(undefined4 **)(iVar1 + 0xb8) = puVar2;
    registerObject(puVar2);

    // Allocate large subsystem E (0xc20 bytes, vtable 0x00e3ecf0) at +0xbc
    puVar2 = (undefined4 *)(*DAT_0119caf0)(0xc20, 0x10); // custom allocator
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        puVar2[3] = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        *puVar2 = &PTR_FUN_00e3ecf0; // vtable
        puVar2[0x304] = 0xffffffff; // initialize some field
    }
    *(undefined4 **)(iVar1 + 0xbc) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem F (0x30 bytes, vtable 0x00e3ec8c) at +0x90
    puVar2 = (undefined4 *)allocateMemory(0x30, 0);
    uVar4 = DAT_00e44740;
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        puVar2[4] = DAT_00e44740;
        puVar2[8] = uVar4;
        uVar4 = DAT_00e4473c;
        puVar2[5] = DAT_00e4473c;
        puVar2[9] = uVar4;
        uVar4 = DAT_00e44738;
        puVar2[6] = DAT_00e44738;
        puVar2[10] = uVar4;
        uVar4 = DAT_00e44734;
        *puVar2 = &PTR_LAB_00e3ec8c; // vtable
        puVar2[7] = uVar4;
        puVar2[0xb] = uVar4;
    }
    *(undefined4 **)(iVar1 + 0x90) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem G (4 bytes, vtable 0x00e3e928) at +0x94
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e928;
    }
    *(undefined4 **)(iVar1 + 0x94) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem H (4 bytes, vtable 0x00e3e948) at +0x98
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e948;
    }
    *(undefined4 **)(iVar1 + 0x98) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem I (4 bytes, vtable 0x00e3e968) at +0x9c
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e968;
    }
    *(undefined4 **)(iVar1 + 0x9c) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem J (0x20 bytes) at +0xa0
    iVar3 = allocateMemory(0x20, 0);
    if (iVar3 == 0) {
        uVar4 = 0;
    } else {
        uVar4 = FUN_005ca060(); // custom constructor
    }
    *(undefined4 *)(iVar1 + 0xa0) = uVar4;
    registerObject(uVar4);

    // Allocate subsystem K (8 bytes, vtable 0x00e3e988) at +0xa4
    puVar2 = (undefined4 *)allocateMemory(8, 0);
    uVar4 = DAT_00e2b1a4;
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e988;
        puVar2[1] = uVar4;
    }
    *(undefined4 **)(iVar1 + 0xa4) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem L (4 bytes, vtable 0x00e3e9a8) at +0xa8
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e9a8;
    }
    *(undefined4 **)(iVar1 + 0xa8) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem M (4 bytes, vtable 0x00e3e9e8) at +0xb0
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
    } else {
        *puVar2 = &PTR_LAB_00e3e9e8;
    }
    *(undefined4 **)(iVar1 + 0xb0) = puVar2;
    registerObject(puVar2);

    // Allocate subsystem N (4 bytes, vtable 0x00e3ecd0) at +0xb4
    puVar2 = (undefined4 *)allocateMemory(4, 0);
    if (puVar2 != (undefined4 *)0x0) {
        *puVar2 = &PTR_LAB_00e3ecd0;
        *(undefined4 **)(iVar1 + 0xb4) = puVar2;
        registerObject(puVar2);
        return;
    }
    *(undefined4 *)(iVar1 + 0xb4) = 0;
    registerObject(0);
    return;
}