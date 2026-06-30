// FUNC_NAME: SimNpc::SimNpc

// Constructor for SimNpc (NPC simulation object)
// Initializes base class (Entity/Sentient?) and multiple embedded sub-objects.
// Parameter param_2 likely contains initialization data (spawn params, etc.)
undefined4 * __thiscall SimNpc::SimNpc(SimNpc *this, undefined4 initData)
{
  // Call base class constructor (probably Entity or Sentient)
  Entity::Entity(&this->base, initData);

  // Call some initialization routine
  FUN_006f7610();

  // Set vtable pointer for this class (main SimNpc vtable)
  this->vtable = &SimNpc::vtable;          // +0x00

  // Set vtable pointers for embedded sub-objects (likely interfaces or state machines)
  // Offset 0x0F (60 bytes) - e.g., some AI or physics component
  this->component1 = &Component1::vtable;  // +0x3C

  // Offset 0x12 (72 bytes) - e.g., state machine
  this->stateMachine = &StateMachine::vtable; // +0x48

  // Offset 0x24 (144 bytes) - e.g., animation controller
  this->animController = &AnimController::vtable; // +0x90

  // Initialize various flags, counters, and sentinel values
  this->flags = 0;                          // +0xC4 (0x31 * 4)
  this->some16Bit = 0;                      // +0xC8 (0x32 * 4) - 16-bit
  this->other16Bit = 0;                     // +0xCA (offset 202)
  this->sentinel1 = 0xBADBADBA;             // +0xCC (0x33 * 4)
  this->sentinel2 = 0xBADBADBA;             // +0xDC (0x37 * 4)
  this->field_at_0x3F = 0;                  // +0xFC (0x3F * 4) - 0xFC
  this->field16bit_0x40 = 0;                // +0x100 (0x40 * 4) - 16-bit
  this->field16bit_0x41 = 0;                // +0x102
  this->field_at_0x41 = 0;                  // +0x104 (0x41 * 4)
  this->field_at_0x42 = 0;                  // +0x108
  this->field_at_0x43 = 0;                  // +0x10C
  this->field_at_0x44 = 0;                  // +0x110
  this->field_at_0x3A = 0;                  // +0xE8
  this->field_at_0x39 = 0;                  // +0xE4
  this->field_at_0x38 = 0;                  // +0xE0
  // Note: sentinel2 was set to 0xBADBADBA above, then reset to 0 here
  this->sentinel2 = 0;                      // +0xDC
  this->field_at_0x3D = 0;                  // +0xF4
  this->field_at_0x3E = 0;                  // +0xF8
  this->field_at_0x36 = 0;                  // +0xD8
  this->field_at_0x35 = 0;                  // +0xD4
  this->field_at_0x34 = 0;                  // +0xD0
  this->sentinel1 = 0;                      // +0xCC

  // Another initialization routine
  FUN_006f2410();

  return this;
}