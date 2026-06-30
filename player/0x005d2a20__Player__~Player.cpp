// FUNC_NAME: Player::~Player

void __thiscall Player::~Player(Player* this, byte deletingFlag)
{
    // Set vtable to derived class vtable to allow virtual calls during destruction
    this->vtable = &PTR_FUN_00e3ede8; // Derived vtable

    // Destroy member at offset +0x48 (player's state machine, e.g., PlayerSM or CoverState)
    if (this->m_pStateMachine != nullptr) {
        // Call destructor for the state machine object
        FUN_009c8f10(this->m_pStateMachine);
    }

    // Switch vtable to base class vtable (Sentient/Entity) for base cleanup
    this->vtable = &PTR_LAB_00e3edec; // Base vtable

    // Reset global flag indicating player instance is being torn down
    g_bPlayerDestroyed = 0; // DAT_012234fc

    // If this is a delete operation (deletingFlag bit 0 set), deallocate memory
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete
    }
}