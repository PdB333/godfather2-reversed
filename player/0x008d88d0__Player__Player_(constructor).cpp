// FUNC_NAME: Player::Player (constructor)
void __fastcall Player::Player(Player *this)
{
    // Set up vtable pointers for multiple inheritance
    this->vtable = &PTR_FUN_00d7da48; // +0x00 primary vtable
    this->vtable2 = &PTR_LAB_00d7da38; // +0x3C secondary vtable
    this->vtable3 = &PTR_LAB_00d7da34; // +0x48 tertiary vtable
    this->vtable4 = &PTR_LAB_00d7da30; // +0x50 quaternary vtable
    this->vtable5 = &PTR_LAB_00d7d9d0; // +0x54 quinary vtable
    this->vtable6 = &PTR_LAB_00d7d968; // +0x58 senary vtable
    // Call base class constructors or initialization routines
    FUN_00472400();
    FUN_0046ea20();
}