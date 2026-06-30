// FUNC_NAME: GodfatherGameManager::processFrame
void __thiscall GodfatherGameManager::processFrame(int this) {
    // +0x2120: pointer to a subsystem (e.g., DonControlManager or CrimeManager)
    this->updateCore(); // always called
    if (*(int *)(this + 0x2120) != 0) {
        this->processSubsystem(); // called if subsystem is active
    }
}