// FUNC_NAME: Player::Player
void __fastcall Player::Player(Player *this)
{
    int *pManager;

    // Set base class vtable (likely Sentient or Entity)
    this->vtable = (void *)&PTR_LAB_00d6bb4c;

    // Initialize flags/subsystems (0xf and 0xb are likely bit flags)
    FUN_007f6420(0xf);
    FUN_007f6420(0xb);

    // Get a manager singleton (e.g., PlayerManager or GameManager)
    pManager = (int *)FUN_007ab150();

    // Call a virtual function on the manager, passing a member at offset 0x74
    // This might be registering the player or setting up a reference
    (*(void (**)(void))(*(int *)pManager + 4))(this->field_0x74);

    // Initialize another subsystem (parameter 2 might be player index or type)
    FUN_007ab2a0(2);

    // Set derived class vtable (Player's own vtable)
    this->vtable = (void *)&PTR_LAB_00d6b95c;

    // Final initialization (e.g., set default state)
    FUN_0080ea60();
}