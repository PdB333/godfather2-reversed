// FUNC_NAME: PlayerMissionComponent::processMissionUpdate
void __fastcall PlayerMissionComponent::processMissionUpdate(void)
{
    uint32_t newTargetID; // uVar3
    int32_t iVar4; // iVar4
    byte savedByte; // uVar1
    MissionManager* pMission; // iVar2

    pMission = (MissionManager*)FUN_006b0ee0(this->currentMissionID);
    if (pMission != (MissionManager*)0x0) {
        if (pMission->stateID == this->currentTargetID) {
            FUN_008c7330(); // e.g., MissionManager::activateCurrentObjective
            if ((this->flags >> 1 & 1) != 0) {
                FUN_006b59f0(); // e.g., MissionManager::onObjectiveComplete
                return;
            }
        }
        else {
            savedByte = *(byte*)(DAT_0112a590 + 4); // global debug state
            if ((this->flags & 1) != 0) {
                FUN_0084ab30(0); // e.g., Debug::printMessage
            }
            newTargetID = pMission->stateID; // previous target
            FUN_006b68c0(this->currentTargetID, 0, 0, 0); // e.g., MissionManager::setTarget
            if ((this->pCallbackObject != (void*)0x0) && (this->currentTargetID == 0x637b907)) {
                iVar4 = FUN_008c74d0(0x637b907); // e.g., EntityDataManager::getEntityByHash
                FUN_008c10d0(this->pCallbackObject, pMission); // e.g., CrimeSceneManager::attachMission
            }
            if ((this->flags & 1) == 0) {
                if (iVar4 == 0) {
                    iVar4 = FUN_008c74d0(this->currentTargetID);
                }
                newTargetID = FUN_008c74d0(newTargetID);
                FUN_006be8a0(iVar4, newTargetID, pMission); // e.g., MissionManager::transitionState
            }
            else {
                FUN_0084ab30(savedByte); // debug output
            }
            if ((this->flags >> 1 & 1) != 0) {
                FUN_006b59f0();
                return;
            }
        }
    }
}