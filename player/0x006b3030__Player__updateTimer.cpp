// FUNC_NAME: Player::updateTimer
void __fastcall Player::updateTimer(Player* this)
{
    // Check if there is an active timer object and if the game is not paused
    if (this->timerObject != 0 && g_gamePaused == 0) {
        // Decrease remaining time by frame delta
        if (this->timerRemaining > 0.0f) {
            this->timerRemaining -= g_frameDeltaTime;
        }
        // If timer expired, trigger the callback and clear
        if (this->timerRemaining <= 0.0f) {
            FUN_008c7d30(this->timerObject, this);  // Destroy or remove timer object
            this->timerObject = 0;
            FUN_006b2f70();  // Notify timer expiration
        }
    }
}