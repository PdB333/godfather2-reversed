// FUNC_NAME: Player::Player
void* __thiscall Player::Player(Player* this, byte flags) {
    // Call base class constructor (Sentient)
    Sentient::Sentient(this); // base constructor at 0x004f02a0
    // If flag bit 0 is set, perform additional initialization
    if ((flags & 1) != 0) {
        Player::additionalInit(this); // e.g., player-specific setup at 0x009c8eb0
    }
    return this;
}