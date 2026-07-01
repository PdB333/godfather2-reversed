// Xbox PDB: EARS_Apt_UIFrontend_ShowRestrictedAccountPopup
// FUNC_NAME: OnlineMenu::showOnlineRestrictedDialog
void OnlineMenu::showOnlineRestrictedDialog(void)
{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = DAT_01223484;
  if (((DAT_01223484 != 0) &&
      (*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0)) &&
     ((undefined4 *)(DAT_01223484 + 0x28) != (undefined4 *)0x0)) {
    *(undefined4 *)(DAT_01223484 + 0x28) = 0;
    *(undefined4 *)(iVar1 + 0x2c) = 0;
  }
  iVar1 = DAT_012234b8;
  FUN_00566b70(); // likely some initialization or cleanup
  iVar2 = FUN_009c8e50(0xf0); // allocate or create menu object (0xf0 = 240 bytes)
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_00982280(0); // initialize menu with parameter 0
  }
  *(undefined4 *)(iVar2 + 0xc) = 0xb; // set menu type/ID to 11
  if ((*(uint *)(iVar1 + 0x2c) >> 0xc & 1) == 0) {
    pcVar3 = "$mp_online_restricted_permissions"; // localized string key
  }
  else {
    pcVar3 = "$ea_onlinerestricted"; // alternative localized string key
  }
  FUN_00981eb0(pcVar3); // set dialog title/description
  FUN_00981e70("$mp_continue_wo_online",1,0); // add button "Continue without online"
  FUN_00982400(1); // set dialog flags (e.g., modal)
  *(undefined1 **)(iVar2 + 0x14) = &LAB_00933a70; // set callback function pointer
  FUN_00982e10(); // show/display the dialog
  return;
}