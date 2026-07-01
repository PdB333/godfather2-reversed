// FUNC_NAME: Player::getSpeed
float __thiscall Player::getSpeed(Player *this) {
    // +0x1d0: pointer to movement component (e.g., MovementComponent*)
    // +0x188: base speed float
    if (this->m_pMovementComponent != 0) {
        // MovementComponent +0x54: speed modifier float
        return this->m_pMovementComponent->m_speedModifier * this->m_baseSpeed;
    }
    return 0.0f;
}