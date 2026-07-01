// FUNC_NAME: TargetSelector::renderOptions

void __fastcall TargetSelector::renderOptions(void *this)
{
    int iVar1;
    char *pcStr;
    uint uIdx;
    void **ppvArray;
    char acBuffer[32]; // +0x20 size

    // Initialize UI context for select target display
    iVar1 = FUN_009c8e50(0xf0); // allocate temporary data
    uIdx = 0;
    if (iVar1 == 0) {
        iVar1 = 0;
    }
    else {
        iVar1 = FUN_00982280(&LAB_0097dc60); // construct UI context
    }
    FUN_00981eb0("$dv_select_target"); // set title string
    *(int *)(iVar1 + 0xc) = 0; // clear some flag

    // Iterate over first array (e.g., primary targets)
    if (*(int *)(this + 0x30) != 0) {
        ppvArray = (void **)(this + 0x10);
        do {
            // Format name from object's string ID (+0xB4) and add to list
            FUN_005c4630(acBuffer, 0x20, &PTR_LAB_00d78708, *(int *)(*ppvArray + 0xb4));
            FUN_00981e70(acBuffer, (int)*(void **)(this + 0xa0) == (int)*ppvArray, 0);
            uIdx++;
            ppvArray++;
        } while (uIdx < *(uint *)(this + 0x30));
    }

    // Second array (e.g., secondary targets)
    uIdx = 0;
    if (*(int *)(this + 0x54) != 0) {
        ppvArray = (void **)(this + 0x34);
        do {
            FUN_005c4630(acBuffer, 0x20, &PTR_LAB_00d78708, *(int *)(*ppvArray + 0xb4));
            FUN_00981e70(acBuffer, (int)*(void **)(this + 0xa0) == (int)*ppvArray, 0);
            uIdx++;
            ppvArray++;
        } while (uIdx < *(uint *)(this + 0x54));
    }

    // Third array (e.g., tertiary targets)
    uIdx = 0;
    if (*(int *)(this + 0x78) != 0) {
        ppvArray = (void **)(this + 0x58);
        do {
            FUN_005c4630(acBuffer, 0x20, &PTR_LAB_00d78708, *(int *)(*ppvArray + 0xb4));
            FUN_00981e70(acBuffer, (int)*(void **)(this + 0xa0) == (int)*ppvArray, 0);
            uIdx++;
            ppvArray++;
        } while (uIdx < *(uint *)(this + 0x78));
    }

    // Fourth array with special handling (e.g., dynamic objects)
    uIdx = 0;
    if (*(int *)(this + 0x9c) != 0) {
        ppvArray = (void **)(this + 0x7c);
        do {
            // Check object type field at +0xC4
            if (*(int *)(*ppvArray + 0xc4) == 9) {
                iVar1 = FUN_008ff310(*(int *)(*ppvArray + 0x38));
                if (iVar1 != 0) {
                    FUN_008fdfb0();
                    pcStr = (char *)FUN_00790610(); // get name string from object
                    if (*pcStr != '\0') {
                        FUN_00981e70(pcStr, (int)*(void **)(this + 0xa0) == (int)*ppvArray, 0);
                    }
                }
            }
            else {
                pcStr = (char *)FUN_006b2160(); // get default name
                if (pcStr == (char *)0x0) {
                    pcStr = &DAT_0120546e; // empty string
                }
                if (*pcStr != '\0') {
                    FUN_00981e70(pcStr, (int)*(void **)(this + 0xa0) == (int)*ppvArray, 0);
                }
            }
            uIdx++;
            ppvArray++;
        } while (uIdx < *(uint *)(this + 0x9c));
    }

    // Finalize list rendering
    FUN_00982e10();
    return;
}