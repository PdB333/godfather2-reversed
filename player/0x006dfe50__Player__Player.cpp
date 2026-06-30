// FUNC_NAME: Player::Player
void __thiscall Player::Player(Player *this) {
    // Set virtual function table pointer for Player class
    // +0x00: vtable pointer for Player
    *(int **)this = &g_pPlayerVTable;
    // +0x08: Second vtable pointer (likely for secondary base or interface)
    *(int **)((char *)this + 8) = &g_pPlayerFunctionTable;

    // Clean up sub-objects if they exist (e.g., reinitialization or reset)
    // +0x7B (0x1EC bytes): Pointer to a component, e.g., PlayerCrewLeaderComponent
    if (*(int *)((char *)this + 0x1EC) != 0) {
        Player::freeComponent((Player*)((char *)this + 0x1EC));
    }
    // +0x49 (0x124 bytes): Pointer to another component, e.g., PlayerF2FSM
    if (*(int *)((char *)this + 0x124) != 0) {
        Player::freeComponent((Player*)((char *)this + 0x124));
    }

    // Call base class constructor (e.g., Sentient::Sentient)
    Sentient::Sentient();
}