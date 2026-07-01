// FUNC_NAME: isScenarioActiveConditionMet
bool __cdecl isScenarioActiveConditionMet()
{
    // FUN_004724d0 likely a singleton getter for a manager (e.g., ScenarioManager or GodfatherGameManager)
    // Returns true if manager exists and some sub-object flag at offset 0x30 is set.

    void* manager = getScenarioManager(); // placeholder name for FUN_004724d0
    if (manager != nullptr)
    {
        // FUN_00471610 likely returns a pointer to a sub-object from the manager (e.g., current scenario instance)
        void* scenarioInstance = getCurrentScenarioInstance(); // placeholder name for FUN_00471610
        // Check flag at offset 0x30 (e.g., m_bIsActive or m_bInitialized)
        // FUN_006c0050 appears to be a boolean check function: arguments (object, offset?, param1, param2)
        // Here it is called as checkFlag(scenarioInstance + 0x30, 1, 1)
        bool flagSet = checkFlag((char*)scenarioInstance + 0x30, 1, 1); // placeholder name for FUN_006c0050
        if (flagSet)
        {
            return true;
        }
    }
    return false;
}