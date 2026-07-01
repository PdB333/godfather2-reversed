// FUNC_NAME: UI::createRollOutButton
void UI::createRollOutButton(void)
{
  // Call to UI creation function with parameters:
  // - "RollOutButton" - button name/type
  // - 0 - unknown flag/parameter
  // - &DAT_00d8c174 - pointer to data/configuration
  // - 1 - count or flag
  // - PTR_DAT_00e5743c - pointer to parent/container
  FUN_005a04a0("RollOutButton",0,&DAT_00d8c174,1,PTR_DAT_00e5743c);
  return;
}