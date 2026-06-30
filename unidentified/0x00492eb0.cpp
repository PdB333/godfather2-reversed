// FUN_00492eb0: InputController::initDefaults
void __thiscall InputController::initDefaults(InputController *this)
{
  // Call base class initialization (likely clears memory or sets up common fields)
  __thiscall BaseInputClass::initBase(this);
  
  uint32 defaultVal = DAT_00e2b1a4;   // global constant for default state
  uint32 outroVal = DAT_00e44628;     // another global constant

  // Set vtable pointer (class identity) at offset 0x00
  this->vtable = &PTR_LAB_00e34a50;   // +0x00: vtable

  // -----------------------------------------------------------------
  // Zero out a section of the object (offsets 0x1C0 – 0x260)
  // -----------------------------------------------------------------
  this->field_0x70 = 0;               // +0x1C0 (uint32)
  *(uint64*)((uint8*)this + 0x1D0) = 0; // +0x1D0 (8 bytes)
  *(uint64*)((uint8*)this + 0x1D8) = 0; // +0x1D8 (8 bytes)
  this->field_0x7C = 0;               // +0x1F0
  this->field_0x7D = 0;               // +0x1F4
  this->field_0x7E = 0;               // +0x1F8
  this->field_0x90 = 0;               // +0x240
  this->field_0x93 = 0;               // +0x24C
  this->field_0x98 = 0;               // +0x260

  // -----------------------------------------------------------------
  // Initialize four controller‑slot structures (each 5 x uint32 = 20 bytes)
  // Slot layout: [state0, zero, zero, zero, zero]  (first field set to defaultVal)
  // -----------------------------------------------------------------
  // Slot 0 at +0x200 (offset 0x80 * 4)
  this->slot0.firstField = defaultVal;
  this->slot0.padding1   = 0;
  this->slot0.padding2   = 0;
  this->slot0.padding3   = 0;
  this->slot0.padding4   = 0;

  // Slot 1 at +0x214 (offset 0x85 * 4)
  this->slot1.firstField = defaultVal;
  this->slot1.padding1   = 0;
  this->slot1.padding2   = 0;
  this->slot1.padding3   = 0;
  this->slot1.padding4   = 0;

  // Slot 2 at +0x228 (offset 0x8A * 4)
  this->slot2.firstField = defaultVal;
  this->slot2.padding1   = 0;
  this->slot2.padding2   = 0;
  this->slot2.padding3   = 0;
  this->slot2.padding4   = 0;

  // Slot 3 at +0x23C (offset 0x8F * 4)
  this->slot3.firstField = defaultVal;
  this->slot3.padding1   = 0;
  this->slot3.padding2   = 0;
  this->slot3.padding3   = 0;
  this->slot3.padding4   = 0;

  // -----------------------------------------------------------------
  // Store a second constant into two adjacent fields
  // -----------------------------------------------------------------
  this->field_0x91 = outroVal;        // +0x244
  this->field_0x92 = outroVal;        // +0x248

  // -----------------------------------------------------------------
  // Zero three more 8‑byte blocks
  // -----------------------------------------------------------------
  *(uint64*)((uint8*)this + 0x250) = 0; // +0x250
  *(uint64*)((uint8*)this + 0x258) = 0; // +0x258
  *(uint64*)((uint8*)this + 0x264) = 0; // +0x264
}