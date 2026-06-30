// FUNC_NAME: SimNpc::~SimNpc
void __thiscall SimNpc::~SimNpc(void* thisx) {
    int* piVar4;
    int* piVar2;
    int* piVar3;
    int iVar5;
    short* psVar1;
    int* piVar6;
    int local_4;

    // Set vtable pointers to base class (assumed)
    // +0x00: vtable for primary base
    // +0x3C, +0x48, +0x50, +0x54, +0x58, +0x2E0, +0x2E4: additional interface vtables
    *(void**)thisx = &g_vtable_SimNpc;          // +0x00
    *(void**)((int)thisx + 0x3C) = &g_vtable_Base1;   // +0x3C
    *(void**)((int)thisx + 0x48) = &g_vtable_Base2;   // +0x48
    *(void**)((int)thisx + 0x50) = &g_vtable_Base3;   // +0x50
    *(void**)((int)thisx + 0x54) = &g_vtable_Base4;   // +0x54
    *(void**)((int)thisx + 0x58) = &g_vtable_Base5;   // +0x58
    *(void**)((int)thisx + 0x2E0) = &g_vtable_Base6;  // +0x2E0
    *(void**)((int)thisx + 0x2E4) = &g_vtable_Base7;  // +0x2E4

    // Release 4 reference-counted component objects (array at +0x744, stride 20 bytes)
    piVar3 = (int*)((int)thisx + 0x744);  // +0x1d1 * 4
    local_4 = 4;
    do {
        FUN_0055af20(); // likely debug assert or pre-release hook
        piVar4 = (int*)*piVar3;
        if (piVar4 != 0) {
            // Decrement reference count at offset +4
            piVar2 = piVar4 + 1;
            *piVar2 = *piVar2 - 1;
            if (*piVar2 == 0) {
                // Call destructor at vtable+4
                (**(void(__thiscall**)(int*))(*piVar4 + 4))(piVar4);
            }
            *piVar3 = 0; // null pointer after release
        }
        piVar3 += 5; // next component (5 ints = 20 bytes)
        local_4--;
    } while (local_4 != 0);

    // Handle timeout callback struct at +0x3A0
    psVar1 = (short*)*(int*)((int)thisx + 0x3A0); // +0xE8
    if (psVar1 != 0) {
        if (*(short*)(psVar1 + 1) != 0) { // check active flag at offset +2
            *(short*)((int)psVar1 + 6) = *(short*)((int)psVar1 + 6) - 1; // decrement timer at offset +6
            if (*(short*)((int)psVar1 + 6) == 0) {
                // Fire callback with argument 1
                (**(void(__cdecl*)(int))*psVar1)(1);
            }
        }
    }

    // Check flag at +0x480 to process 4 more objects
    if (*(int*)((int)thisx + 0x480) != 0) {
        piVar6 = (int*)((int)thisx + 0x3C0); // +0xF0*4
        iVar5 = 4;
        do {
            if (*(int*)((int)thisx + 0x218) != 0) {
                FUN_00572c50(piVar6); // release another object
            }
            piVar6 += 0xC; // 12 bytes per element
            iVar5--;
        } while (iVar5 != 0);
    }

    // Logging/event processing if counter at +0x164 is non-zero
    if (*(int*)((int)thisx + 0x164) != 0) {
        // Send four event parameters to debug log system
        for (int j = 0; j < 4; j++) {
            int eventVal = *(int*)((int)thisx + 0x710 + j*4); // +0x1C4..0x1C7
            if (eventVal != 0) {
                // Simulate EA's debug log buffer push (global pointer at DAT_01206880+0x14)
                int** logPtr = (int**)(DAT_01206880 + 0x14); // global log buffer stack pointer
                **logPtr = (int)&PTR_LAB_01124668; // push marker
                *logPtr += 4;
                **logPtr = eventVal;
                *logPtr += 4;
                **logPtr = (int)((int)thisx + 0x54); // push field at +0x54 ("puVar1")
                *logPtr += 4;

                // If the counter reaches 0 after decrement, push end marker
                if (*(int*)((int)thisx + 0x164) != 0) {
                    int newCount = *(int*)((int)thisx + 0x164) - 1;
                    *(int*)((int)thisx + 0x164) = newCount;
                    if (newCount == 0) {
                        int** logPtr2 = (int**)(DAT_01206880 + 0x14);
                        **logPtr2 = (int)&PTR_LAB_0110ba58; // end marker
                        *logPtr2 += 4;
                        // Push a bitmasked address (this or field?)
                        **logPtr2 = (uint)(-((int)thisx != 0)) & (uint)((int)thisx + 0x54);
                        *logPtr2 += 4;
                    }
                }
            }
        }
    }

    // Clear three pairs of pointers (offset +0x798, +0x784, +0x770)
    iVar5 = 3;
    piVar3 = (int*)((int)thisx + 0x798); // +0x1E6
    do {
        int* piVar4Prev = piVar3 - 5; // step back 20 bytes
        // Null two pointers at offsets -4 and 0 from previous base
        if (piVar3[-4] != 0) {
            *(int*)(piVar3[-4] + 8) = 0; // clear back-pointer?
            piVar3[-4] = 0;
        }
        if (*piVar4Prev != 0) {
            *(int*)(*piVar4Prev + 8) = 0;
            *piVar4Prev = 0;
        }
        iVar5--;
        piVar3 = piVar4Prev;
    } while (-1 < iVar5);

    // Final release calls (likely deallocate memory or additional cleanup)
    iVar5 = 3;
    do {
        FUN_004bfcf0();
        iVar5--;
    } while (-1 < iVar5);
    FUN_00544450();

    return;
}