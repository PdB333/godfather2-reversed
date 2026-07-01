// FUNC_NAME: UIButton::setActiveState
void __fastcall UIButton::setActiveState(int this)
{
  if (*(char *)(this + 0x50) == '\0') {
    // Button is inactive, activate it
    FUN_005a04a0("ActivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c);
    return;
  }
  // Button is active, deactivate it
  FUN_005a04a0("DeactivateButton", 0, &DAT_00d8c174, 1, PTR_DAT_00e5743c);
  return;
}