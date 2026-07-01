// FUNC_NAME: PlayerCrewLeaderComponent::shutdown
void __fastcall PlayerCrewLeaderComponent::shutdown(PlayerCrewLeaderComponent* thisPtr)
{
    // Release first allocated resource if present (e.g., crew member list)
    if (*(int32_t*)((uint8_t*)thisPtr + 0x1e18) != 0) {
        FUN_004df600(); // Operator delete or resource release
    }

    // Release second resource (e.g., pending crew info)
    if (*(int32_t*)((uint8_t*)thisPtr + 0x1e2c) != 0) {
        FUN_004df600(); // Operator delete or resource release
    }

    // Check if game is still active (e.g., not exiting entirely)
    bool isGameActive = FUN_0089c630() != 0;
    if (isGameActive) {
        // Notify parent Player object at offset -0x58 of this component's shutdown
        // This is typically the containing Player instance as this component is
        // embedded at offset 0x58 in Player's layout.
        Player* parentPlayer = reinterpret_cast<Player*>(
            reinterpret_cast<uint8_t*>(thisPtr) - 0x58);
        FUN_008a0c90(parentPlayer); // Player::onCrewComponentShutdown
    }
}