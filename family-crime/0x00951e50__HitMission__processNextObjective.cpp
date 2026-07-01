// FUNC_NAME: HitMission::processNextObjective
// Function address: 0x00951e50
// Role: Check if current mission objective slot is available and trigger initialization if conditions met
// Fields:
// +0x48: bool bObjectiveListReady (flag1)
// +0x4c: bool bCurrentObjectiveActive (flag2)
// +0x78: uint32 currentObjectiveIndex
// +0x5c: uint32 totalObjectivesCount
// +0x58: void** objectiveArray (array of pointers to objective objects)

void __thiscall HitMission::processNextObjective(HitMission* this, uint32 playerId) {
    // Check conditions: both flags set, index within bounds, and slot is null
    if ((((this->bObjectiveListReady != 0) && (this->bCurrentObjectiveActive != 0)) &&
        (this->currentObjectiveIndex < this->totalObjectivesCount)) &&
        (*(this->objectiveArray + this->currentObjectiveIndex) == (void*)0x0)) {
        // Trigger event type 6 and play notification
        triggerEvent(6, playerId); // e.g., spawn or activate objective
        triggerNotification(); // e.g., sound/UI cue
    }
}