// Xbox PDB: EARS_Modules_Sentient_InitializeBoneMods
// FUNC_NAME: MobFaceManager::initializeMorphTargets
// Address: 0x007fb040
// This function initializes facial morph target arrays for a character.
// It sets up arrays for eye, eyelid, cheek, and other facial bones.
// The virtual function at vtable+0x94 is likely getMorphTargetHandle(const char* name, ...)
// FUN_0045ed50 is likely an array allocation/initialization function.

void __fastcall MobFaceManager::initializeMorphTargets(int *thisPtr)
{
    int iVar1;
    char cVar2;
    uint unaff_ESI; // unknown register value from caller
    uint unaff_EDI; // unknown register value from caller
    char *pcVar3;
    int *piStack_100;
    int **ppiStack_fc;
    int *piStack_f8;
    undefined4 ***pppuStack_f4;
    int *piStack_f0;
    int **ppiStack_ec;
    int *piStack_e8;
    char ***pppcStack_e4;
    int *piStack_e0;
    int **ppiStack_dc;
    int *piStack_d8;
    undefined1 **ppuStack_d4;
    int *piStack_d0;
    char **ppcStack_cc;
    int *piStack_c8;
    undefined1 **ppuStack_c4;
    int *piStack_c0;
    int **ppiStack_bc;
    int *piStack_b8;
    undefined1 **ppuStack_b4;
    int *piStack_b0;
    char **ppcStack_ac;
    int *piStack_a8;
    undefined1 **ppuStack_a4;
    int *piStack_a0;
    char **ppcStack_9c;
    int *piStack_98;
    undefined4 **ppuStack_94;
    int *piStack_90;
    char **ppcStack_8c;
    int *piStack_88;
    undefined1 *puStack_84;
    char *pcStack_80;
    undefined1 *puStack_7c;
    int *piStack_78;
    undefined1 *puStack_74;
    char *pcStack_70;
    undefined1 *puStack_6c;
    char *local_68;
    undefined4 *puStack_64;
    char *pcStack_60;
    undefined4 local_48[11];
    undefined4 uStack_1c;
    undefined4 uStack_18;

    // Initialize some fields with global constants
    iVar1 = _DAT_00d5780c; // some default value (maybe -1 or 0)
    thisPtr[0x244] = DAT_00d5d7b8;
    thisPtr[0x245] = DAT_00e447a4;
    thisPtr[0x246] = 0;
    thisPtr[0x247] = 0;
    thisPtr[0x248] = 0;
    thisPtr[0x24e] = 0;
    thisPtr[0x24d] = 0;
    thisPtr[0x24c] = 0;
    thisPtr[0x24f] = iVar1;
    thisPtr[0x252] = 0;
    thisPtr[0x251] = 0;
    thisPtr[0x250] = 0;
    thisPtr[0x253] = iVar1;
    thisPtr[0x256] = 0;
    thisPtr[0x255] = 0;
    thisPtr[0x254] = 0;
    thisPtr[599] = iVar1; // offset 0x95C? Actually 599*4 = 0x95C
    thisPtr[0x25a] = 0;
    thisPtr[0x259] = 0;
    thisPtr[600] = 0; // offset 0x960
    thisPtr[0x25b] = iVar1;
    thisPtr[0x25d] = -1;

    pcStack_60 = (char *)0x7fb120; // some string or address
    FUN_007f7050(); // unknown helper
    pcStack_60 = (char *)0x1;
    *(undefined1 *)(thisPtr + 0x288) = 1; // set byte at offset 0x288 to 1
    thisPtr[0x261] = 0;
    thisPtr[0x262] = 0;
    thisPtr[0x263] = 0;
    puStack_64 = (undefined4 *)0x1;
    local_68 = (char *)0x0;
    *(undefined1 *)(thisPtr + 0x28c) = 0;
    *(undefined1 *)((int)thisPtr + 0xa31) = 0;
    thisPtr[0x28d] = 0;
    thisPtr[0x28e] = 0;
    puStack_6c = (undefined1 *)0x7fb171;
    FUN_007f49e0(); // unknown helper

    puStack_74 = (undefined1 *)((uint)thisPtr[0x1ba] >> 2); // size/4
    if ((((puStack_74 != (undefined1 *)0x0) && ((thisPtr[0x1bb] & 0xfffffffcU) != 0)) &&
        ((thisPtr[0x1b7] & 0xfffffffcU) != 0)) && ((thisPtr[0x1b8] & 0xfffffffcU) != 0))
    {
        // Initialize morph target arrays for various facial bones
        // Each block: set up stack variables, call virtual function to get handle,
        // if handle valid, call FUN_0045ed50 to allocate array.

        // eye_R
        pcStack_60 = (char *)0x0;
        puStack_64 = (undefined4 *)0x0;
        local_68 = (char *)0x0;
        puStack_6c = (undefined1 *)0x0;
        pcStack_70 = (char *)0x5; // element size?
        piStack_78 = thisPtr + 0x2b0; // buffer for eye_R morph
        puStack_7c = (undefined1 *)0x7fb1be; // string "eye_R"
        FUN_0045ed50(); // allocate array: (buffer, size/4, 5, 0)

        // eye_L
        pcStack_60 = (char *)0x0;
        puStack_64 = (undefined4 *)0x0;
        local_68 = (char *)0x0;
        puStack_6c = (undefined1 *)0x0;
        pcStack_70 = (char *)0x5;
        puStack_74 = (undefined1 *)((uint)thisPtr[0x1bb] >> 2);
        piStack_78 = thisPtr + 700; // 0x2BC? Actually 700*4 = 0x2BC
        puStack_7c = (undefined1 *)0x7fb1dc; // "eye_L"
        FUN_0045ed50();

        // levatPalp_L (levator palpebrae left)
        pcStack_60 = (char *)0x0;
        puStack_64 = (undefined4 *)0x0;
        local_68 = (char *)0x0;
        puStack_6c = (undefined1 *)0x0;
        pcStack_70 = (char *)0x5;
        puStack_74 = (undefined1 *)((uint)thisPtr[0x1b7] >> 2);
        piStack_78 = thisPtr + 0x2c8;
        puStack_7c = (undefined1 *)0x7fb1fa; // "levatPalp_L"
        FUN_0045ed50();

        // corrugator_L
        pcStack_60 = (char *)0x0;
        puStack_64 = (undefined4 *)0x0;
        local_68 = (char *)0x0;
        puStack_6c = (undefined1 *)0x0;
        pcStack_70 = (char *)0x5;
        puStack_74 = (undefined1 *)((uint)thisPtr[0x1b8] >> 2);
        piStack_78 = thisPtr + 0x2d4;
        puStack_7c = (undefined1 *)0x7fb218; // "corrugator_L"
        FUN_0045ed50();

        // Now use virtual function to get handles for eye_R and eye_L
        pcStack_60 = "eye_R";
        puStack_64 = local_48;
        local_48[0] = 0;
        local_68 = (char *)0x7fb236; // some string?
        (**(code **)(*thisPtr + 0x94))(); // virtual call with "eye_R"

        local_68 = "eye_L";
        puStack_6c = &stack0xffffffac;
        pcStack_70 = (char *)0x7fb24c;
        (**(code **)(*thisPtr + 0x94))(); // virtual call with "eye_L"

        // cheek_UL (upper left cheek)
        pcStack_70 = (char *)0x0;
        puStack_74 = (undefined1 *)0x0;
        piStack_78 = (int *)0x0;
        puStack_7c = (undefined1 *)0x0;
        pcStack_80 = (char *)0x5;
        puStack_84 = (undefined1 *)(unaff_EDI >> 2); // size from register
        piStack_88 = thisPtr + 0x2ec;
        ppcStack_8c = (char **)0x7fb268; // "cheek_UL"
        FUN_0045ed50();

        // cheek_UR (upper right cheek)
        pcStack_70 = (char *)0x0;
        puStack_74 = (undefined1 *)0x0;
        piStack_78 = (int *)0x0;
        puStack_7c = (undefined1 *)0x0;
        pcStack_80 = (char *)0x5;
        puStack_84 = (undefined1 *)(unaff_ESI >> 2); // size from register
        piStack_88 = thisPtr + 0x2e0;
        ppcStack_8c = (char **)0x7fb284; // "cheek_UR"
        FUN_0045ed50();

        // levatPalp_L again? (different offset)
        pcStack_70 = "levatPalp_L";
        puStack_74 = &stack0xffffffac;
        uStack_1c = 0;
        uStack_18 = 0;
        piStack_78 = (int *)0x7fb2aa;
        cVar2 = (**(code **)(*thisPtr + 0x94))(); // virtual call
        if (cVar2 != '\0') {
            piStack_78 = (int *)0x0;
            puStack_7c = (undefined1 *)0x0;
            pcStack_80 = (char *)0x0;
            puStack_84 = (undefined1 *)0x0;
            piStack_88 = (int *)0x301; // element size?
            ppcStack_8c = (char **)(unaff_EDI >> 2);
            piStack_90 = thisPtr + 0x304;
            ppuStack_94 = (undefined4 **)0x7fb2cd;
            FUN_0045ed50();
        }

        // Another morph (maybe "levatPalp_R"?)
        piStack_78 = (int *)0xd71e60; // global data
        puStack_7c = &stack0xffffffa8;
        pcStack_80 = (char *)0x7fb2e3;
        cVar2 = (**(code **)(*thisPtr + 0x94))();
        if (cVar2 != '\0') {
            pcStack_80 = (char *)0x0;
            puStack_84 = (undefined1 *)0x0;
            piStack_88 = (int *)0x0;
            ppcStack_8c = (char **)0x0;
            piStack_90 = (int *)0x301;
            ppuStack_94 = (undefined4 **)((uint)pcStack_60 >> 2);
            piStack_98 = thisPtr + 0x2f8;
            ppcStack_9c = (char **)0x7fb306;
            FUN_0045ed50();
        }

        // corrugator_L again
        pcStack_80 = "corrugator_L";
        puStack_84 = &stack0xffffffa4;
        piStack_88 = (int *)0x7fb320;
        cVar2 = (**(code **)(*thisPtr + 0x94))();
        if (cVar2 != '\0') {
            piStack_88 = (int *)0x0;
            ppcStack_8c = (char **)0x0;
            piStack_90 = (int *)0x0;
            ppuStack_94 = (undefined4 **)0x0;
            piStack_98 = (int *)0x301;
            ppcStack_9c = (char **)((uint)puStack_64 >> 2);
            piStack_a0 = thisPtr + 0x34c;
            ppuStack_a4 = (undefined1 **)0x7fb343;
            FUN_0045ed50();
        }

        // ... many more similar blocks for other morph targets
        // (abbreviated for clarity; the pattern repeats for each bone)

        // Final block for cheek_UL and cheek_UR
        pcVar3 = "cheek_UL";
        piStack_f8 = (int *)0x0;
        cVar2 = (**(code **)(*thisPtr + 0x94))(&piStack_f8, "cheek_UL");
        if (cVar2 != '\0') {
            FUN_0045ed50(thisPtr + 0x370, (uint)piStack_100 >> 2, 0x301, 0, 0, 0, 0);
        }

        piStack_100 = (int *)0x0;
        cVar2 = (**(code **)(*thisPtr + 0x94))(&piStack_100, "cheek_UR");
        if (cVar2 != '\0') {
            FUN_0045ed50(thisPtr + 0x37c, (uint)pcVar3 >> 2, 0x301, 0, 0, 0, 0);
        }
    }
    return;
}