// FUNC_NAME: MissionManager::startCutscene
undefined4 MissionManager::startCutscene(undefined4 param_1, undefined4 *param_2)
{
  // Store cutscene-related data from param_2
  // +1 offset: cutscene ID or similar
  DAT_010c2658 = param_2[1];
  // +2 offset: additional cutscene parameter (e.g., time or flags)
  DAT_011947e4 = param_2[2];

  // Process the cutscene command using the first parameter (e.g., cutscene name)
  FUN_004e27a0(*param_2);

  // Set some state flag (1 = playing or starting)
  FUN_0051f540(1);

  // Execute cutscene setup logic
  FUN_004e2870();

  // Reset cutscene state when done
  DAT_010c2658 = 0xffffffff; // Invalid/stopped sentinel
  DAT_011947e4 = 0;           // Clear additional parameter

  return 1; // Success
}