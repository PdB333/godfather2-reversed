// FUNC_NAME: Player::destructor
void __fastcall Player::~Player(undefined4 *this)
{
  // Set vtable pointers - note the double underscore suggesting final overrider vtable
  *this = &PTR_FUN_00d69cd4;  // vtable entry for ~Player
  this[0xf] = &PTR_LAB_00d69cc4;  // vtable entry (probably another destructor level)
  this[0x12] = &PTR_LAB_00d69cc0; // vtable entry (probably yet another base class)

  FUN_00792200(this); // sub-object destructor call #1
  FUN_00792560(this); // sub-object destructor call #2

  // Release two mutexes or critical sections (common pattern in EARS objects)
  FUN_004086d0(&DAT_012069c4); // Destroy mutex at global address 0x012069c4
  FUN_004086d0(&DAT_0120e93c); // Destroy mutex at global address 0x0120e93c

  // Free audio-related resource at offset +0xB4 (+0x2d * 4)
  if (this[0x2d] != 0) {
    (*(code *)this[0x30])(this[0x2d]); // Call through function pointer at +0xC0
  }

  // Release vector/list at +0xA4 (+0x29 * 4)
  if (this[0x29] != 0) {
    FUN_004daf90(this + 0x29); // Vector destructor
  }

  // Release vector/list at +0x9C (+0x27 * 4)  
  if (this[0x27] != 0) {
    FUN_004daf90(this + 0x27); // Vector destructor
  }

  // Free resource at +0x60 (+0x18 * 4)
  if (this[0x18] != 0) {
    (*(code *)this[0x1b])(this[0x18]); // Call deallocator at +0x6C
  }

  FUN_0046c640(); // Cleanup some global state
  return;
}