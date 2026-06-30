// FUNC_NAME: Player::getCurrentActionState
// Address: 0x00544b70
// Role: Getter for the player's current action state. Dereferences a pointer at +0x360 from the player object to access a sub-component (likely PlayerSM), then reads an integer at +0x10c from that component.

int __thiscall Player::getCurrentActionState()
{
    // this+0x360 -> pointer to PlayerSM
    // PlayerSM+0x10c -> current action state (e.g., enum or handle)
    return *(int*)(*(int*)((char*)this + 0x360) + 0x10c);
}