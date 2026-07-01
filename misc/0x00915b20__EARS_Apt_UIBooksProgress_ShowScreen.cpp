// Xbox PDB: EARS_Apt_UIBooksProgress_ShowScreen
// FUNC_NAME: LoadingManager::showLoadingScreens
void __fastcall LoadingManager::showLoadingScreens(undefined4 *param_1)
{
  // Show the initial loading screen
  FUN_005a04a0("ShowScreen",0,&DAT_00d84448,1,"Progress");
  
  // Step 0: Initialize loading state
  *param_1 = 0;
  FUN_00914c50(); // LoadingManager::loadStep0
  
  // Step 1: Load core assets
  *param_1 = 1;
  FUN_00914b10(); // LoadingManager::loadStep1
  
  // Step 2: Load game data
  *param_1 = 2;
  FUN_00914d70(); // LoadingManager::loadStep2
  
  // Hide the progress screen
  FUN_005a04a0("ProgressShowScreen",0,&DAT_00d84448,0);
  
  return;
}