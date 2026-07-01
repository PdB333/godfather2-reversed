// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_ConfirmNoAction
// FUNC_NAME: PopupManager::showCancelConfirmPopup
void __thiscall PopupManager::showCancelConfirmPopup(int this, byte param_2)
{
  int iVar1;
  char *pcVar2;
  
  iVar1 = FUN_009c8e50(0xf0); // allocate memory for popup data (size 0xF0)
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0); // initialize popup object
  }
  if (*(int *)(this + 100) == 1) { // +0x64: popup type (1=defenders)
    pcVar2 = "$popup_defenders_cancel_confirm";
  }
  else if (*(int *)(this + 100) == 2) { // +0x64: popup type (2=attackers)
    pcVar2 = "$popup_attackers_cancel_confirm";
  }
  else {
    pcVar2 = "$popup_bombing_cancel_confirm"; // default: bombing cancel
  }
  FUN_00981eb0(pcVar2); // set popup text from string table
  *(undefined4 *)(iVar1 + 0xc) = 2; // +0x0C: popup state/type
  *(undefined4 *)(iVar1 + 0x20) = 0xb9754031; // +0x20: callback function pointer
  *(undefined4 *)(iVar1 + 0x1c) = 0x997dee17; // +0x1C: callback function pointer
  *(undefined1 **)(iVar1 + 0x14) = &LAB_0097f2c0; // +0x14: function pointer
  *(uint *)(iVar1 + 0x10) = (uint)param_2; // +0x10: parameter for callback
  FUN_00982e10(); // show popup / update UI
  return;
}