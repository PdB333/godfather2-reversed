// FUNC_NAME: Player::checkCondition
// Address: 0x0080e220
// Role: Evaluates various action conditions for the player state machine.
//       conditionId is expected in range 10-23 (after subtracting 10 for switch).

bool __thiscall Player::checkCondition(int conditionId, int a2, int a3, int a4, int a5)
{
    char cVar;
    bool result = false;
    float local_24, fStack_20, local_18, local_14, local_10;
    double local_c; // part of position vector
    float local_4;  // y component of position
    int playerObj;
    int objAtPos;

    switch(conditionId - 10) {
    case 0: // conditionId == 10
        // checks if some state at +0x90 is 0
        return *(int*)(this + 0x90) == 0;

    case 1: // conditionId == 11
        return *(int*)(this + 0x90) == 1;

    case 2: // conditionId == 12
        // calls some condition check function (e.g., isInAir?)
        cVar = isCharacterInSpecialState(); // FUN_0080e0b0
        return cVar == 0;

    case 3: // conditionId == 13
        if (*(int*)(this + 0x60) == 0)
            return false;
        return *(int*)(this + 0x60) != 0x48; // compare with idle state?

    case 4: // conditionId == 14
        return isCharacterInSpecialState(); // FUN_0080e0b0 (non-zero check)

    case 5: // conditionId == 15
        cVar = isPlayerAlive(); // FUN_00481620
        if (cVar == 0)
            return false;
        playerObj = getLocalPlayer(); // FUN_00471610
        // check if player's character type matches target type? Both branches same after optimization
        if (*(int*)(this + 0x58) == 0)
            cVar = isCharacterTypeValid(playerObj + 0x30); // FUN_009a8870
        else
            cVar = isCharacterTypeValid(playerObj + 0x30);
        goto checkAndReturn;

    case 6: // conditionId == 16
        cVar = isConditionA(); // FUN_0080df70
        goto condCheck;

    case 7: // conditionId == 17
        cVar = isConditionB(); // FUN_0080e010
condCheck:
        if (cVar != 0) {
            cVar = isPlayerAlive();
checkAndReturn:
            if (cVar != 0)
                return true;
        }
        return false;

    case 9: // conditionId == 19 - predictive targeting
        if ((*(byte*)(this + 0x94) & 1) != 0)
            break; // flags indicate already satisfied? Return false later
        playerObj = getLocalPlayer();
        // Extract player position (Vec3 at playerObj+0x30)
        local_c = *(double*)(playerObj + 0x30); // x component as double
        local_4 = *(float*)(playerObj + 0x38); // y or z component?
        
        // Calculate offset based on time and speed
        int actor = *(int*)(this + 0x58); // current actor/state?
        int baseActor = (actor != 0) ? (actor - 0x48) : 0;
        int baseActor2 = (actor != 0) ? (actor - 0x48) : 0;
        // Get velocity vector from baseActor offsets (+0x1a8, +0x1b0) and a scalar from fVar6
        // Actually reading as doubles then casting to float (likely a misdecompile)
        local_24 = (float)*(double*)(baseActor2 + 0x1a8);
        // The next line is (float)((uint64)*(double*)(baseActor2+0x1a8) >> 32) which is weird
        // likely a workaround for a vector component. We'll approximate as float.
        fStack_20 = (float)((uint64)*(double*)(baseActor2 + 0x1a8) >> 32); // probably y component of velocity
        if (actor != 0)
            baseActor2 = actor - 0x48;
        float fVar6 = *(float*)(baseActor2 + 0x1bc) + someGlobalTimeFactor; // DAT_00d5f520
        // Calculate predicted position
        local_18 = local_24 * speedFactor * fVar6 + (float)local_c; // DAT_00d5ccf8
        local_14 = fStack_20 * speedFactor * fVar6 + local_4; // likely z or x?
        local_10 = *(float*)(baseActor2 + 0x1b0) * speedFactor * fVar6 + *(float*)(baseActor + 0x194); // third component
        
        // Find object at predicted position
        objAtPos = findObjectAtPosition(*(int*)(this + 0x50), &local_18, &local_18, 1); // FUN_009a76f0
        if (objAtPos != 0) {
            if (*(int*)(objAtPos + 0x24) == 0) {
                setPlayerFocus(0); // FUN_0044b210
                return false;
            }
            setPlayerFocus(*(int*)(objAtPos + 0x24) - 0x48); // adjust to object base
            return false;
        }
        break;

    case 10: // conditionId == 20 - check if in idle state
        if (*(int*)(this + 0x58) == 0 || *(int*)(this + 0x58) == 0x48)
            return true;
        // else check bit (possibly in combat or something)
        if (*(int*)(this + 0x58) == 0)
            return (bool)(~*(byte*)(this + 0x58 + 8) & 1); // Ghidra artifact
        return (bool)(~*(byte*)(this + 0x58 - 8) & 1); // read flag near state

    case 0xC: // conditionId == 22
        if ((*(uint*)(this + 0x94) >> 2 & 1) != 0) { // flags bit 2 set
            cVar = isPlayerAlive();
            if (cVar != 0) {
                cVar = isPlayerInAction(); // FUN_007f47a0
                if (cVar != 0)
                    return true;
            }
            // Check another flag and a global player state
            if (((*(byte*)(this + 0x94) & 1) != 0) &&
                (*(char*)(*(int*)(this + 0x50) + 0x2438) == 0)) // some external state
                return true;
        }
        break;

    case 0xD: // conditionId == 23
        if (((*(uint*)(*(int*)(this + 0x68) + 0x4c) >> 1 & 1) == 0) &&
            isConditionC() == 0) // FUN_009955e0
            return false;
        return true;

    default:
        // For conditions outside the handled range, delegate to base class
        result = baseCheckCondition(a2, a3, conditionId, a5); // FUN_004ac640
        break;
    }
    return result;
}