// FUNC_NAME: CrewMission::evaluateTrigger
// Function address: 0x0073a930
// Role: Checks mission completion conditions and triggers event 0x10000 if satisfied

void __thiscall CrewMission::evaluateTrigger(void* thisPtr) {
    int missionScenario;
    int player;
    int conditionData;

    conditionData = *(int*)((char*)thisPtr + 0x5c); // +0x5c: pointer to scenario-specific data

    if (conditionData == 0) {
        missionScenario = 0;
    } else {
        missionScenario = getActiveMission(DAT_01131040); // global SimManager pointer
    }

    player = getPlayer(); // returns player object pointer

    if ((((missionScenario != 0) &&
          ((*(unsigned char*)(missionScenario + 0x44) & 0x40) != 0)) &&               // check flag at +0x44 bit 6
         ((player == 0 || ((*(unsigned int*)(player + 0x5c) >> 0x1d & 1) == 0)))) &&  // player not in cutscene/blocked state
        (conditionData = evaluateCondition(conditionData, DAT_00d5ccf8, DAT_00d5d70c),
         conditionData != 0)) {
        triggerEvent(0x10000); // trigger mission completed/action event
    }
}