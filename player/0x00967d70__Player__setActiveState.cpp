// FUNC_NAME: Player::setActiveState
void __thiscall Player::setActiveState(int this, int newState)
{
    // +0x1F4 (500): likely a state flag (0/1) for player active/idle
    *(char *)(this + 500) = (char)newState;
    // +0xD3 in global game manager: mirror of the state flag
    *(char *)(DAT_01129914 + 0xD3) = (char)newState;
    // Propagate state change to other systems
    FUN_0095eb90(newState);
}