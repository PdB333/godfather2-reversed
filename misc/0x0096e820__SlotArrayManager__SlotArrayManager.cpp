// FUNC_NAME: SlotArrayManager::SlotArrayManager

// Constructor for SlotArrayManager class.
// Initializes an array of slots (16 max) and a counter, setting one default slot.
// Based on decompilation of function at 0x0096e820.
// Structure layout (offsets in bytes):
//   +0x00: vtable pointer
//   +0x04: pointer to some static data (maybe secondary vtable)
//   +0x68: int slots[16]  (at +0x1a words)
//   +0xA8: int slotCount  (at +0x2a words)
__thiscall SlotArrayManager::SlotArrayManager(SlotArrayManager* this)
{
  // Call base class constructor (unknown)
  UnknownBaseClass::UnknownBaseClass(this);

  this->slotCount = 0;                                 // +0xA8 = 0
  this->vtable = (void**)&PTR_FUN_00d8ede0;            // +0x00: set vtable
  this->somePointer = (void*)&PTR_LAB_00d8edb8;       // +0x04: secondary pointer

  // If there is room (always true since slotCount is 0), add a default slot
  if ((uint)this->slotCount < 0x10) {
    this->slots[this->slotCount] = 2;                  // +0x68 + slotCount*4
    this->slotCount = this->slotCount + 1;             // increment count to 1
  }

  return this;
}