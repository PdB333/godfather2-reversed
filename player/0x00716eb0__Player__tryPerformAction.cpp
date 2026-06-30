// FUNC_NAME: Player::tryPerformAction
void __fastcall Player::tryPerformAction(Player *this)
{
    char paused;
    int gameState;
    int iVar2;
    int isBusy;
    undefined4 target;
    float power;

    // Check if gameplay is allowed (e.g., not paused, not fading)
    paused = isGameplayAllowed(); // FUN_007f47a0
    if (paused == 0) {
        gameState = getGameState(); // FUN_0077dd80
        if (gameState == 3) { // kGameState_Playing
            // +0x338: mCurrentActionObject (e.g., weapon, vehicle target)
            if (this->mCurrentActionObject != 0) {
                iVar2 = this->mCurrentActionObject - 0x48; // likely offset to some sub-component
                if (iVar2 != 0) {
                    isBusy = isPlayerBusy(); // FUN_00800a90, e.g., in cover, interacting
                    // +0x18: mEntity (Sentient*), +0x8e0: mFlags bitfield
                    if ((isBusy == 0) || (((this->mEntity->mFlags >> 10) & 1) == 0)) {
                        target = getActionTarget(); // FUN_007f7c60 (e.g., camera, input)
                        setActionContext(target);   // FUN_007eea50
                        // Compute interaction power/distance between entity and action object
                        power = (float)computeActionFactor(this->mEntity, iVar2); // FUN_00711fb0
                        applyActionEffect(iVar2, power); // FUN_007eef50 (e.g., apply damage, force)
                        return;
                    }
                }
            }
        }
    }
    // Fallback: clear/reset action
    clearAction(); // FUN_007eea00
}