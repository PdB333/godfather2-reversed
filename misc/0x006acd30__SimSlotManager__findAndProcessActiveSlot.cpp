// FUNC_NAME: SimSlotManager::findAndProcessActiveSlot
// Address: 0x006acd30
// This method searches through a fixed-size array of 20 slot descriptors (each 12 bytes) to find
// the first slot where both flags[bit1] is set and the type field equals 3. Once found, it reads
// a 4-byte value from a parallel array (each entry 48 bytes) at the same index and passes it to
// a processing function.
// Offsets relative to this:
// +0x2C: start of SlotDescriptor array (20 entries, each 0xC bytes)
//   struct SlotDescriptor { int flags; int unknown; int type; } // +0x00, +0x04, +0x08
// +0x38: start of SlotData array (20 entries, each 0x30 bytes), first 4 bytes used as argument

void __fastcall SimSlotManager::findAndProcessActiveSlot(SimSlotManager* this)

{
  int index;
  int* typePtr;
  
  index = 0;
  // typePtr points to the type field of the first SlotDescriptor (this+0x34)
  typePtr = (int *)((char *)this + 0x34);
  while ((((uint)typePtr[-2] >> 1 & 1) == 0 || (*typePtr != 3))) {
    index = index + 1;
    typePtr = typePtr + 3; // advance by 12 bytes (3 ints)
    if (0x13 < index) {
      return;
    }
  }
  // Index found, retrieve the corresponding 4-byte value from the SlotData array (stride 0x30)
  FUN_00894c90(*(undefined4 *)(index * 0x30 + 0x38 + (int)this));
  return;
}