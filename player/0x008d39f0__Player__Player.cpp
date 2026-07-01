// FUNC_NAME: Player::Player

void __fastcall Player::Player(Player *this)
{
    // +0x00: vtable pointer for Player
    *this = (Player*)&PTR_FUN_00d7d4d8;
    
    // +0x4C: secondary vtable pointer (for multiple inheritance or interface)
    this->field_0x4C = (int*)&PTR_LAB_00d7d4c8;
    
    // Initialize two sub-objects at offsets 0x58 and 0x68
    // Likely state machines or component objects (e.g., PlayerGroundSM, PlayerWallCoverSM)
    initSubObject(reinterpret_cast<uint32_t*>(this) + 0x16); // offset 0x58
    initSubObject(reinterpret_cast<uint32_t*>(this) + 0x1a); // offset 0x68
    
    // Call base class constructors
    baseClassInit1(); // e.g., Entity::Entity
    baseClassInit2(); // e.g., Sentient::Sentient
}