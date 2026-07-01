// FUNC_NAME: CSACrewComponent::showAreYouSureDialog
void CSACrewComponent::showAreYouSureDialog(void)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0xf0); // allocate 0xF0 bytes for dialog data
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0); // initialize dialog with parent 0 (root)
  }
  FUN_00981eb0("$hud_csa_are_you_sure"); // set dialog text from localization key
  *(undefined4 *)(iVar1 + 0xc) = 2; // +0x0C: dialog type (2 = yes/no confirmation)
  *(undefined4 *)(iVar1 + 0x20) = 0xb9754031; // +0x20: callback function hash for "yes"
  *(undefined4 *)(iVar1 + 0x1c) = 0x997dee17; // +0x1C: callback function hash for "no"
  *(undefined1 **)(iVar1 + 0x14) = &LAB_0092c190; // +0x14: pointer to callback handler function
  FUN_00982e10(); // show the dialog
  return;
}