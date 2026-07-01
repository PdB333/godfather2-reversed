// Xbox PDB: EARS_Apt_UIFrontend_StartButtonPressed
// FUNC_NAME: GameStateManager::showTitleScreen
void GameStateManager::showTitleScreen(void)

{
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined1 uStack_4;
  
  // Set some global state flag to 0x25 (37 decimal) - likely a screen/menu ID
  DAT_00e5672c = 0x25;
  
  // Call virtual function at offset 4 from some object (likely a singleton or manager)
  // This is probably a "show" or "activate" method
  (**(code **)(*DAT_01129924 + 4))();
  
  // Hide title text and legal text via some UI function
  FUN_005a04a0("HideTitleText",0,&DAT_00d8963c,0);
  FUN_005a04a0("HideLegalText",0,&DAT_00d8963c,0);
  
  // Call another virtual function at offset 0x28 from a different object
  // This is likely a "reset" or "initialize" method for the title screen
  (**(code **)(*DAT_01129a74 + 0x28))();
  
  // Set up a local structure and call a function to handle it
  uStack_c = DAT_01130448;
  uStack_8 = 0;
  uStack_4 = 0;
  FUN_00408a00(&uStack_c,0);
  
  return;
}