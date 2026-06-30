// FUNC_NAME: Player::Player
void __fastcall Player::Player(Player *this)
{
    // Set initial vtable pointers (base class vtables)
    this->vtable = &PTR_FUN_00d588bc;          // +0x00: primary vtable (base)
    this->vtable2 = &PTR_LAB_00d588ac;         // +0x3C: secondary vtable (interface 1)
    this->vtable3 = &PTR_LAB_00d588a8;         // +0x48: tertiary vtable (interface 2)

    // Call base class constructor (e.g., Sentient::Sentient)
    FUN_0078ecf0(this);

    // Override vtables with derived class implementations
    this->vtable = &PTR_FUN_00d5888c;          // +0x00: Player primary vtable
    this->vtable2 = &PTR_LAB_00d5887c;         // +0x3C: Player secondary vtable
    this->vtable3 = &PTR_LAB_00d58878;         // +0x48: Player tertiary vtable

    // Call derived class initialization (e.g., Player::init)
    FUN_0046c640(this);
}