// FUNC_NAME: PlayerCoverStateMachine::processCoverPhases
void __thiscall PlayerCoverStateMachine::processCoverPhases(int thisPtr, undefined4 phaseParam) {
    // phaseParam is likely a reference to cover state data
    setPhaseTimer(phaseParam);                          // reset phase progress
    setPhaseDuration(phaseParam, 80.9f);                // set max time for phase (80.9 seconds)
    
    bool allPhasesComplete = areAllPhasesComplete();    // check if all three phases done
    
    do {
        if (allPhasesComplete) {
            return;
        }
        
        advancePhaseIterator();                         // move to next sub-step within current phase
        
        int currentPhase = getCurrentPhaseIndex();      // returns 0, 1, or 2
        
        if (currentPhase == 0) {
            advancePhaseIterator();                     // additional step for phase 0
            void* phaseData = getPhaseData();           // retrieve data for phase 0
            int dataArraySlot = thisPtr + 0x290;        // +0x290: phase data array slot 0
            setPhaseDataAtIndex(dataArraySlot, phaseData);
        }
        else if (currentPhase == 1) {
            advancePhaseIterator();
            void* phaseData = getPhaseData();
            int dataArraySlot = thisPtr + 0x298;        // +0x298: phase data array slot 1
            setPhaseDataAtIndex(dataArraySlot, phaseData);
        }
        else if (currentPhase == 2) {
            advancePhaseIterator();
            void* phaseData = getPhaseData();
            int dataArraySlot = thisPtr + 0x2a0;        // +0x2a0: phase data array slot 2
            setPhaseDataAtIndex(dataArraySlot, phaseData);
        }
        
        finalizePhaseUpdate();                          // commit changes for current phase
        allPhasesComplete = areAllPhasesComplete();
    } while (true);
}