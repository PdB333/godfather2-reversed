// FUNC_NAME: PresentationManager::prepareToHideScreen
void PresentationManager::prepareToHideScreen(void)
{
  // Calls the engine function to prepare for hiding the screen
  // The string "PrepareToHideScreen" is a command identifier
  // DAT_00d8f99c is likely a pointer to a callback or data structure
  FUN_005a04a0("PrepareToHideScreen",0,&DAT_00d8f99c,0);
  return;
}