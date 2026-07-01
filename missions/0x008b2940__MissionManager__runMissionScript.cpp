// FUNC_NAME: MissionManager::runMissionScript
void __thiscall MissionManager::runMissionScript(void *this, undefined4 missionId)
{
  char retryFlag;
  int scriptResult;
  
  // Initialize mission script with the given ID
  MissionScript::load(missionId);
  ScriptEngine::executeOpcode(missionId, 0x4f642506); // Opcode for mission start
  
  // Loop until mission completes or fails
  retryFlag = ScriptEngine::isPaused();
  while (retryFlag == '\0') {
    // Advance script execution
    ScriptEngine::tick();
    scriptResult = ScriptEngine::getResult();
    if (scriptResult == 0) {
      // Mission succeeded, get result data
      scriptResult = ScriptEngine::tick();
      *(undefined4 *)((int)this + 100) = *(undefined4 *)(scriptResult + 8); // +0x64 missionResultData
    }
    // Update script state
    ScriptEngine::update();
    retryFlag = ScriptEngine::isPaused();
  }
  return;
}