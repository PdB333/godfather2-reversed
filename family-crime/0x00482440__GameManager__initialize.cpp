// FUNC_NAME: GameManager::initialize
// Constructor/initializer for GameManager class.
// Sets vtable pointer (+0x00) and initializes a count field (+0x04) to 0,
// then registers the object with a global list or performs setup via FUN_0049c6e0.
GameManager* __fastcall GameManager::initialize(GameManager* this)
{
    this->vtable = &PTR_FUN_00e33648; // +0x00: vtable pointer
    this->field_0x4 = 0;               // +0x04: count or handle
    FUN_0049c6e0(&DAT_00e33640, 1);    // global registration/initialization
    return this;
}