// FUNC_NAME: Player::processInputState
void __thiscall Player::processInputState(bool forceUpdate)
{
    // Handler for audio bank retrieval
    undefined4 audioBankHandle;
    int bnkStreamMgr;
    
    if (forceUpdate) {
        // Fetch audio bank 2 (likely UI sounds)
        audioBankHandle = AudioDataManager::getBank(2);
        // Cast to BNKStreamManager for stream status check
        bnkStreamMgr = static_cast<BNKStreamManager*>(audioBankHandle);
        // +0x8 in BNKStreamManager is stream data pointer; 0 means not loaded
        if (*(int *)(bnkStreamMgr + 8) == 0) {
            // Load UI audio bank 1
            AudioDataManager::loadBank(1);
        }
    }
    // Check flag at +0x2c6c (bit 6) – probably "ignore controller input"
    if ((*(uint *)(this + 0x2c6c) >> 6 & 1) == 0) {
        // Update controller mode based on state at +0x2c74
        updateControllerMode(*(int *)(this + 0x2c74) != 0);
    }
}