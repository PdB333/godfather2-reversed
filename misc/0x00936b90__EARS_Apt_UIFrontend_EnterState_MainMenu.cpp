// Xbox PDB: EARS_Apt_UIFrontend_EnterState_MainMenu
// FUNC_NAME: MainMenuManager::initMainMenu
void MainMenuManager::initMainMenu(int param_2)
{
  int *piVar1;
  char cVar2;
  undefined1 uVar3;
  char *languageStr;
  int iVar4;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;

  // Call some initialization function
  someInitFunction();
  // Set a flag at global offset +0x3a3 to 1
  *(undefined1 *)(DAT_01129a74 + 0x3a3) = 1;
  // Clear field at this+0xa8
  *(undefined4 *)(this + 0xa8) = 0;
  // Call function with parameter 0 (maybe disable something)
  FUN_008a43b0(0);
  // Set a flag at global offset +0xd3 to 0
  *(undefined1 *)(DAT_01129914 + 0xd3) = 0;
  // Check if some condition (maybe language detection)
  cVar2 = FUN_00566920();
  if (cVar2 == '\0') {
    // Clear bit 0x10000 in global flags
    DAT_01130590 = DAT_01130590 & 0xfffeffff;
  }
  else {
    // Set bit 0x10000 in global flags
    DAT_01130590 = DAT_01130590 | 0x10000;
  }
  // Build a Flash function call: "EnableMenuItem" with parameters
  buildFlashCall(&local_c, 8, &DAT_00e3266c, 4);
  invokeFlashFunction("EnableMenuItem", 0, &DAT_00d8963c, 2, &local_c, &DAT_00e36d94);
  // Schedule something (maybe a timer) with callback at LAB_00930c00, delay 1
  scheduleCallback(this + 0x10, &LAB_00930c00, 1);
  // Clear bit 0x400 in global flags
  DAT_01130590 = DAT_01130590 & 0xfffffbff;
  // Set up a locale structure
  local_c = DAT_011303e8;
  local_8 = 0;
  local_4 = 0;
  // Initialize locale
  initLocale(&local_c, 0);
  // Get language string (e.g., "en")
  languageStr = (char *)getLanguageString(0xffffffff);
  if (languageStr != (char *)0x0) {
    iVar4 = __stricmp(languageStr, "en");
    if (iVar4 == 0) {
      // Set field at this+0x71 to 1 (English)
      *(undefined1 *)(this + 0x71) = 1;
      goto LAB_00936c8a;
    }
  }
  // Otherwise set to 0 (non-English)
  *(undefined1 *)(this + 0x71) = 0;
LAB_00936c8a:
  // Check if video is playing
  cVar2 = isVideoPlaying();
  if (cVar2 == '\0') {
    // Tell Flash to go to frame "fr_main"
    invokeFlashFunction("gotoAndStop", 0, &DAT_00d8963c, 1, "fr_main");
    piVar1 = DAT_01129924;
    if (DAT_01129924 != (int *)0x0) {
      cVar2 = isVideoPlaying();
      if (cVar2 != '\0') {
        // Call function pointer at offset 4 (maybe video finished callback)
        (**(code **)(*piVar1 + 4))();
      }
      // Play video "mainmenu.vp6" with parameters 7 and 2
      playVideo("mainmenu.vp6", 7, 2);
    }
  }
  // Check if some global state is valid
  if (((DAT_01223484 == 0) ||
      (*(int *)(DAT_01223484 + 0x28) == 0 && *(int *)(DAT_01223484 + 0x2c) == 0)) ||
     (DAT_01223484 == -0x28)) {
    // If param_2 is 0x18 or 0x19 (menu item indices)
    if ((param_2 == 0x18) || (param_2 == 0x19)) {
      // Set field at this+0x6c to 1
      *(undefined4 *)(this + 0x6c) = 1;
      // Force highlight on menu item
      invokeFlashFunction("ForceHighlight", 0, &DAT_00d8963c, 0);
      // Set bit 0x400 in global flags
      DAT_01130590 = DAT_01130590 | 0x400;
      // Call function pointer at offset 0x2c (maybe menu action)
      (**(code **)(*DAT_01129890 + 0x2c))();
      if (param_2 == 0x19) {
        // Set bit 0x2 in global flags
        DAT_01130590 = DAT_01130590 | 2;
        // Call function for specific menu action
        FUN_00934ab0();
      }
      else {
        // Set some global variable to 0x1c
        DAT_00e5672c = 0x1c;
      }
      // Call another function (maybe update menu)
      FUN_00931010();
    }
  }
  else {
    // If state is not valid, call another function
    FUN_00936790();
  }
  // Get some value and store it at global offset +0x70
  iVar4 = DAT_01129928;
  uVar3 = FUN_008f3c70();
  *(undefined1 *)(iVar4 + 0x70) = uVar3;
  // Tell Flash to initialize main menu
  invokeFlashFunction("InitMainMenu", 0, &DAT_00d8963c, 0);
  return;
}