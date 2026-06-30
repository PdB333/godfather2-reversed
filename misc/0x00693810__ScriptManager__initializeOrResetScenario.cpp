// FUNC_NAME: ScriptManager::initializeOrResetScenario
void ScriptManager::initializeOrResetScenario(void)
{
  long resetType; // eax
  bool isScenarioActive; // al

  // Call base initialization or reset function
  FUN_006911b0(); // likely ScriptManager::baseReset or similar
  isScenarioActive = FUN_0089c630(); // Check if a scenario is currently active, returns bool
  if (isScenarioActive == false) {
    resetType = 1; // No scenario active: reset to initial state (e.g., no scenario)
  }
  else {
    resetType = 6; // Scenario active: reset to restart scenario state
  }
  FUN_006913c0(resetType); // Apply the reset type
  // Set a flag indicating initialization/reset is complete (offset +0x0C)
  *(int *)(FUN_00691a70() + 0xc) = 1; // FUN_00691a70 likely returns pointer to a member structure
  return;
}