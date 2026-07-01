// FUNC_NAME: Player::updatePlayerState
void Player::updatePlayerState(Player* this, float deltaTime)
{
    // Call base class update (likely Sentient::update or similar)
    Sentient::update(this, deltaTime);
    
    // Call player-specific state update
    Player::updateStateMachine(this, deltaTime);
    
    return;
}