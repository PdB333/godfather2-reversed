// FUNC_NAME: ScriptManager::dispatchCommand
// Address: 0x008d46a0
// Dispatches various script commands based on command ID.
// Uses a global script manager (0x637b907) and a global data structure (DAT_011299a8) for family data.
// param_1: command ID (enum)
// param_2: Lua state (lua_State*)
// Returns number of values pushed onto Lua stack.

#define LUA_SCRIPT_MANAGER 0x637b907  // Likely pointer to a global script manager singleton
// DAT_011299a8 is a global pointer to a structure containing family-related data (e.g., FamilyManager)

int ScriptManager::dispatchCommand(int commandId, lua_State* L) {
    int result = 0;

    switch (commandId) {
        case 0:
            result = getFamilyByIndex(0);          // FUN_008d6ac0
            result = pushValueToLua(result, L);    // FUN_008d3d80
            return result;
        case 4:
            result = getFamilyByIndex(1);          // FUN_008d6ae0
            result = pushValueToLua(result, L);    // FUN_008d3d80
            return result;
        case 9:
            result = getScriptManager(LUA_SCRIPT_MANAGER);  // FUN_008d37a0
            result = pushObjectToLua(result, L);            // FUN_008d3dd0
            return result;
        case 0x0e:
            result = getFamilyData(0);              // FUN_008d2d00(0)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x0f:
            result = getFamilyData(2);              // FUN_008d2d00(2)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x10:
            result = getFamilyData(1);              // FUN_008d2d00(1)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x11:
            result = getFamilyData(3);              // FUN_008d2d00(3)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x14:
            result = getFamilyName(L);              // FUN_008d2d20
            result = pushObjectToLua(result);       // FUN_008d3dd0 (no second arg?)
            return result;
        case 0x16:
            result = getScriptManager2(LUA_SCRIPT_MANAGER); // FUN_008d37f0
            result = pushObjectToLua(result, L);            // FUN_008d3dd0
            return result;
        case 0x1b:
            result = getFamilyDataAlt(0);           // FUN_008d2d10(0)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x1c:
            result = getFamilyDataAlt(2);           // FUN_008d2d10(2)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x1d:
            result = getFamilyDataAlt(1);           // FUN_008d2d10(1)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x1e:
            result = getFamilyDataAlt(3);           // FUN_008d2d10(3)
            result = pushObjectToLua(result, L);    // FUN_008d3dd0
            return result;
        case 0x21:
            result = getFamilyTrait(L);             // FUN_008d2d30
            result = pushObjectToLua(result);       // FUN_008d3dd0 (no second arg?)
            return result;
        case 0x22:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x18, L); // FUN_008d3e20
            return result;
        case 0x23:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x30, L); // FUN_008d3e20
            return result;
        case 0x24:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x48, L); // FUN_008d3e20
            return result;
        case 0x25:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x60, L); // FUN_008d3e20
            return result;
        case 0x26:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x7c, L); // FUN_008d3e20
            return result;
        case 0x27:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x28, L); // FUN_008d3e20
            return result;
        case 0x28:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x40, L); // FUN_008d3e20
            return result;
        case 0x29:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x58, L); // FUN_008d3e20
            return result;
        case 0x2a:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x70, L); // FUN_008d3e20
            return result;
        case 0x2b:
            result = getFamilyMemberData((FamilyManager*)DAT_011299a8 + 0x84, L); // FUN_008d3e20
            break;
        case 0x2d:
            result = getFamilyDonor(LUA_SCRIPT_MANAGER); // FUN_008d7bb0
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x32:
            result = getFamilyProperty(0);                // FUN_008d6ad0(0)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x33:
            result = getFamilyProperty(2);                // FUN_008d6ad0(2)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x34:
            result = getFamilyProperty(1);                // FUN_008d6ad0(1)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x35:
            result = getFamilyProperty(3);                // FUN_008d6ad0(3)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x39:
            result = getFamilyBoss(LUA_SCRIPT_MANAGER);   // FUN_008d7c00
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x3e:
            result = getFamilyMember(0);                  // FUN_008d6af0(0)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x3f:
            result = getFamilyMember(2);                  // FUN_008d6af0(2)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x40:
            result = getFamilyMember(1);                  // FUN_008d6af0(1)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
        case 0x41:
            result = getFamilyMember(3);                  // FUN_008d6af0(3)
            result = pushValueToLua(result, L);           // FUN_008d3d80
            return result;
    }
    return result;
}