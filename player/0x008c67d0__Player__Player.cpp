//FUNC_NAME: Player::Player
// Function address: 0x008c67d0
// Role: Constructor for Player class
// Calls base class constructor at 0x008c6450 (likely Entity::Entity)
// If allocFlag (bit 0 of param_2) is set, calls FUN_0043b960(this, 0x234) which may allocate memory or initialize a member

Player* __thiscall Player::Player(Player* this, byte allocFlag) {
    // Call base class constructor
    Entity::Entity(this);
    
    // If allocation flag is set, perform additional initialization
    if (allocFlag & 1) {
        FUN_0043b960(this, 0x234); // Possibly allocate or initialize a member of size 0x234
    }
    
    return this;
}