// FUNC_NAME: NPCCrewComponent::updateCrewState
void __thiscall NPCCrewComponent::updateCrewState(int this) {
    int ownerId = *(int *)(this + 0x40); // +0x40: owner/affiliated entity ID
    setInitialState(ownerId);            // FUN_008c74d0

    int state = *(int *)(this + 0xc4);   // +0xc4: component state (0=idle,1=active)
    if (state != 0) {
        if (state != 1)
            return;

        int playerId = getCurrentPlayerId(); // FUN_0084a410
        if (playerId != 0) {
            playerId = getCurrentPlayerId(); // second call, result used for comparison
            if (playerId != ownerId)
                return;

            char isPlayerActive = isPlayerControlActive(); // FUN_0084a670
            if (isPlayerActive) {
                int target = **(int **)(this + 0xc0); // +0xc0: pointer to target/controlled object
                grantPlayerControl(target);           // FUN_008c2f80
            }
        }
    }
    finalizeUpdate(this); // FUN_008c3ec0
}