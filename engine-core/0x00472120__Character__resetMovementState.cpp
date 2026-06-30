// FUNC_NAME: Character::resetMovementState
void Character::resetMovementState()
{
    // Retrieve pointer to internal animation/movement state (+0x168)
    AnimationState* pAnimState = *(AnimationState**)(this + 0x168);

    // Clear two consecutive flag bytes (+0x60 and +0x61)
    pAnimState->flags1 = 0;  // +0x60
    pAnimState->flags2 = 0;  // +0x61
}