// Xbox PDB: EARS_Modules_TrinityGameScriptedEvents_ParseTrinityEventId
// FUNC_NAME: registerTimeScriptFunctions
// Function address: 0x00845960
// Role: Validates that all required time-related script functions are registered.
// Returns 0 on success, or an error code (1-7) indicating which function is missing.

int registerTimeScriptFunctions()
{
    int result = 0;
    int luaState[3]; // Stack frame for Lua callback context
    code *callbackFunction; // Function pointer for cleanup

    // Check if "restoreTimeState" script function exists
    if (getScriptFunction("restoreTimeState") == 0)
        return 4;

    // Check if "restoreShadowRanges" script function exists
    if (getScriptFunction("restoreShadowRanges") == 0)
        return 6;

    // Push Lua state or setup callback context (likely for error handling)
    setupLuaCallback(luaState, &DAT_00e337ec); // DAT_00e337ec is likely a Lua state or global context

    // Check remaining required script functions
    if (getScriptFunction("changeApparentTime") == 0)
        result = 1;
    else if (getScriptFunction("changeTime") == 0)
        result = 2;
    else if (getScriptFunction("queueChangeTime") == 0)
        result = 3;
    else if (getScriptFunction("setShadowRanges") == 0)
        result = 5;
    else if (getScriptFunction("setTimeScale") == 0)
        result = 7;

    // If a Lua callback context was set up, invoke the cleanup callback
    if (luaState[0] != 0)
        (*callbackFunction)(luaState[0]);

    return result;
}