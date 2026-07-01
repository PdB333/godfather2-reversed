// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_ShowNoLicensePopup
// FUNC_NAME: FamilyManager::showNoLicenseError
void __fastcall FamilyManager::showNoLicenseError(int this)
{
    char cVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    undefined1 *puVar4;
    int iVar5;
    undefined1 *local_1024;
    undefined4 local_1020;
    undefined4 local_101c;
    code *local_1018;
    undefined1 local_1014 [4112];
    undefined4 uStack_4;
    
    uStack_4 = 0x92ae8a;
    FUN_0090a5a0(); // likely some stack setup or debug check
    uVar2 = DAT_012234a4; // global string table or localization manager
    cVar1 = *(char *)(*(int *)(this + 300) + 0x168 + this); // +0x12C: some family member index or state
    FUN_00604be0(); // push/pop string context
    local_1024 = (undefined1 *)0x0;
    local_1020 = 0;
    local_101c = 0;
    local_1018 = (code *)0x0;
    puVar3 = (undefined4 *)FUN_00790610(); // get current language/region
    puVar4 = (undefined1 *)*puVar3;
    if (puVar4 == (undefined1 *)0x0) {
        puVar4 = &DAT_0120546e; // default empty string
    }
    FUN_00604c10(0x6e, puVar4); // set string context (0x6e = 110, likely a string ID)
    FUN_00604c80(0x6d, cVar1 + '\x01'); // set another string context with offset
    FUN_006038a0(uVar2, local_1014, &local_1024, "$pause_family_equip_no_license_error"); // format localized string
    iVar5 = FUN_009c8e50(0xf0); // allocate UI element (0xf0 = 240 bytes)
    if (iVar5 == 0) {
        iVar5 = 0;
    }
    else {
        iVar5 = FUN_00982280(0); // initialize UI element
    }
    puVar4 = local_1024;
    if (local_1024 == (undefined1 *)0x0) {
        puVar4 = &DAT_0120546e; // default empty string
    }
    FUN_00981eb0(puVar4); // set text on UI element
    *(undefined4 *)(iVar5 + 0xc) = 3; // +0x0C: UI element type/state = 3 (likely error dialog)
    *(undefined4 *)(iVar5 + 0x20) = 0x510c352b; // +0x20: some identifier or callback hash
    *(code **)(iVar5 + 0x14) = FUN_0092a710; // +0x14: callback function for button press
    FUN_00982e10(); // show/display the UI element
    if (local_1024 != (undefined1 *)0x0) {
        (*local_1018)(local_1024); // free allocated string
    }
    FUN_00604c00(); // cleanup string context
    return;
}