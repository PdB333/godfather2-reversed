// FUNC_NAME: UISettingsMenu::onConfirmSettings
void UISettingsMenu::onConfirmSettings(void)

{
  int iVar1;
  
  FUN_00983190();
  iVar1 = FUN_009c8e50(0xf0);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0);
  }
  *(undefined4 *)(iVar1 + 0xc) = 2;
  FUN_00981eb0("$ui_controlsetup_settings_confirm");
  *(undefined4 *)(iVar1 + 0x20) = 0x11997e8d;
  *(undefined4 *)(iVar1 + 0x1c) = 0xf29858bb;
  *(undefined1 **)(iVar1 + 0x14) = &LAB_00988630;
  FUN_00982e10();
  return;
}