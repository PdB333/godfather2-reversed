// FUNC_NAME: PlayerSM::constructor
void __fastcall PlayerSM::constructor(PlayerSM *this, int arg2)
{
  // Call base class constructor with type ID 3 and size 0x46 (70)
  FUN_0045d730(this, arg2, 3, 0x46);
  
  // Set vtable pointer to first virtual function table
  this->vtable = &PTR_FUN_00e394d8;
  
  // Set state table entries or function pointers
  this->stateTable[0xf] = &PTR_LAB_00e396f4;   // +0x3C
  this->stateTable[0x12] = &PTR_LAB_00e39704;  // +0x48
  this->stateTable[0x14] = &PTR_LAB_00e39708;  // +0x50
  this->stateTable[0x15] = &PTR_LAB_00e39710;  // +0x54
  this->stateTable[0x16] = &PTR_LAB_00e39770;  // +0x58
  
  // Initialize magic sentinel values (debug markers)
  this->magic1 = 0xbadbadba;  // +0x2C0
  this->magic2 = 0xbeefbeef;  // +0x2C4
  this->magic3 = 0xeac15a55;  // +0x2C8
  this->magic4 = 0x91100911;  // +0x2CC
  
  // Zero out adjacent fields
  this->field_0x2D0 = 0;      // +0x2D0
  this->field_0x2D4 = 0;      // +0x2D4
  this->field_0x2D8 = 0;      // +0x2D8
  
  // Clear magic sentinels (initialization complete)
  this->magic4 = 0;
  this->magic3 = 0;
  this->magic2 = 0;
  this->magic1 = 0;
  
  // Initialize a member object (stack-based constructor call)
  FUN_0043c8f0(&this->someMember);  // Temporary constructor on stack
  
  // Set state flags (bit 0x10 = active state?)
  this->stateFlags |= 0x10;   // +0x148
  this->moreFlags = this->moreFlags; // +0x14C (no-op)
}