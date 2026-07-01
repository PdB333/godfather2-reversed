// FUNC_NAME: MissionManager::tryCompleteObjective
char __thiscall MissionManager::tryCompleteObjective(void* this, char forceComplete, int objectiveId)
{
    int missionStatePtr = *(int*)((int)this + 0x58); // +0x58: pointer to current mission state
    char result;

    if (forceComplete == '\0') {
        result = FUN_00481640(); // likely checks if mission is active
        if (((result != '\0') && (*(char*)(missionStatePtr + 0x21b4) == '\0')) &&
            (*(int*)(missionStatePtr + 0x21bc) == objectiveId)) {
            *(char*)(missionStatePtr + 0x21b4) = 1; // +0x21b4: flag indicating objective completed
            return '\x01';
        }
    } else {
        // force complete path: log or trigger event
        undefined4 local_1c;
        undefined4 uStack_10;
        undefined8 local_c;
        undefined4 local_4;

        local_1c = CONCAT31(local_1c._1_3_, 1); // set first byte to 1
        FUN_0079fb90(1, CONCAT44(3, local_1c), CONCAT44(uStack_10, objectiveId), local_c, local_4);
    }
    return forceComplete;
}