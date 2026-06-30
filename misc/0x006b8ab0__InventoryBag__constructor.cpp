// FUNC_NAME: InventoryBag::constructor
uint* __thiscall InventoryBag::constructor(uint* this, uint param_2)
{
  // Call base class constructor (likely EARSObject or Entity)
  FUN_0046c590(param_2);

  // Set vtable pointer
  *this = &PTR_FUN_00d5e5e8;

  // Two internal buffer pointers (e.g., arrays of item slots)
  this[0xf] = &PTR_LAB_00d5e5d8;  // +0x3C: pointer to main item array
  this[0x12] = &PTR_LAB_00d5e5d4; // +0x48: pointer to secondary item array

  // Clear fields for two slot groups (primary and secondary)
  this[0x14] = 0;                  // +0x50: uint (perhaps count or index)
  *(uint16*)(this + 0x15) = 0;     // +0x54: short (primary slot count)
  *(uint16*)((int)this + 0x56) = 0; // +0x56: short (primary slot capacity?)
  this[0x16] = 0;                  // +0x58: uint
  *(uint16*)(this + 0x17) = 0;     // +0x5C: short (secondary slot count)
  *(uint16*)((int)this + 0x5E) = 0; // +0x5E: short (secondary slot capacity?)

  // Zero out a range of state fields (0x60 to 0x8C)
  this[0x18] = 0;  // +0x60
  this[0x1c] = 0;  // +0x70
  this[0x1b] = 0;  // +0x6C
  this[0x1a] = 0;  // +0x68
  this[0x19] = 0;  // +0x64
  this[0x1d] = 0;  // +0x74
  this[0x1e] = 0;  // +0x78
  this[0x1f] = 0;  // +0x7C
  this[0x20] = 0;  // +0x80
  this[0x21] = 0;  // +0x84
  this[0x22] = 0;  // +0x88
  this[0x23] = 0;  // +0x8C

  // Sentinel values for "no selection"
  this[0x24] = 0xffffffff;  // +0x90: current primary slot index
  this[0x25] = 0xffffffff;  // +0x94: current secondary slot index
  this[0x26] = 0;           // +0x98: some flag

  return this;
}