// FUNC_NAME: Game::constructor
// Function: 0x00486ae0 - Constructor for the Game class.
// Initializes base class, sets derived vtable, and clears global initialization flag.

void __fastcall Game::constructor(Game *this)
{
    // Set the base class vtable pointer
    this->vtable = (void**)&PTR_FUN_00e337b8; // Base vtable
    // Call the base class constructor
    BaseGame::constructor();                   // FUN_004872d0
    // Update to derived class vtable
    this->vtable = (void**)&PTR_LAB_00e337bc; // Derived vtable (Game)
    // Reset the global initialization flag (DAT_01223380)
    gGameInitFlag = 0;
}