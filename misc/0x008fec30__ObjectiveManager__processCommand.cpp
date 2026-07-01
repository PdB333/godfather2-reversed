// FUNC_NAME: ObjectiveManager::processCommand
void __thiscall ObjectiveManager::processCommand(ObjectiveManager* this, int* command)
{
    int commandId = *command;
    // DAT_012069c4 likely "kCmdArriveAtLocation"
    if (commandId == kCmdArriveAtLocation) {
        // Check if arrival objective is active (bit 1 of flags at +0x94)
        if ((((this->flags >> 1) & 1) != 0) && 
            (this->currentObjective != 0) && 
            (this->currentObjective != 0x48) && 
            (isPlayerInRange() != 0)) 
        {
            int playerInfo = getPlayerPosition();
            // Extract position info from the returned struct
            Vector3 pos1;
            pos1.x = *(float*)(playerInfo + 0x30);
            pos1.y = *(float*)(playerInfo + 0x34);
            pos1.z = *(float*)(playerInfo + 0x38);

            int playerInfo2 = getPlayerPosition();
            float dx = *(float*)(playerInfo2 + 0x30) - pos1.x;
            float dy = *(float*)(playerInfo2 + 0x34) - pos1.y;
            float dz = *(float*)(playerInfo2 + 0x38) - pos1.z;

            // Use a square distance check
            if ((dx*dx + dy*dy + dz*dz <= kArrivalThresholdSqr) &&
                (checkLineOfSight(&pos1, 0, 0) == 0))
            {
                markObjectiveActive();
                this->flags |= 4;  // Set bit 2: objective activated
            }
        }
        // Check if completion requirement met (bit 4 of flags)
        if (((this->flags >> 4) & 1) != 0 && canProgress() != 0) {
            markObjectiveFailed();
        }
        // If objective state is 2, finalise and release command
        if (this->objectiveState == 2) {
            updateObjectiveState();
            releaseCommand(command);
            return;
        }
    }
    else if (commandId == this->objectiveId_0) {
        completeObjective(1);
        releaseCommand(command);
        return;
    }
    else if (commandId == this->objectiveId_1) {
        completeObjective(2);
        releaseCommand(command);
        return;
    }
    else if (commandId == this->objectiveId_2) {
        completeObjective(3);
        releaseCommand(command);
        return;
    }
    else if (commandId == kCmdObjectiveFailed) {
        removeCommand(&kCmdObjectiveFailed);
        resetObjectives();
        releaseCommand(command);
        return;
    }
    else if (commandId == kCmdAttackTarget) {
        if (this->currentObjective != 0 && this->currentObjective != 0x48) {
            if (isTargetDefeated() != 0) {
                int index = (this->currentObjective == 0) ? 0 : (this->currentObjective - 0x48);
                if (getGangsterState(index) != 0) {
                    triggerObjectiveAction(0);
                }
            }
        }
    }
    releaseCommand(command);
    return;
}