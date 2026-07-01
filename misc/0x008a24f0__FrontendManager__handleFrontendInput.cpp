// FUNC_NAME: FrontendManager::handleFrontendInput
void FrontendManager::handleFrontendInput(int param_1, int param_2)
{
  int iVar1;
  int iVar2;
  
  // Call base class or helper function
  FUN_00567b10(param_1, param_2);
  
  // Get current game state
  iVar1 = FUN_00683410(*(undefined4 *)(DAT_0112980c + 4));
  
  // Check if we're in the frontend main loop state
  iVar2 = FUN_00683280("FrontendMainLoop");
  
  // If in frontend main loop, param_1 is non-zero, and param_2 is zero,
  // handle the input action
  if (((iVar1 == iVar2) && (param_1 != 0)) && (param_2 == 0)) {
    FUN_0096b160(param_1);
  }
  
  return;
}