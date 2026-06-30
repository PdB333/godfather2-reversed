// FUNC_NAME: EntityManager::allocateEntitySlot
uint __thiscall AllocateEntitySlot(uint *this)
{
  uint index; // uVar1
  uint *slot; // puVar2

  if (*this < 0x90) {
    index = 0;
    slot = this + 0x122a8; // +0x122a8: entity slot allocation flags array (bitset for 0x90 slots)
    do {
      if ((*slot & 1) == 0) {
        this[4] = (uint)(this + (index + 0x2455) * 8); // +0x4: store pointer to allocated slot data
        (this + (index + 0x2455) * 8)[1] = 0; // clear slot flags
        *(undefined4 *)(this[4] + 8) = 0; // slot +0x8: entity ID?
        *(undefined4 *)(this[4] + 0xc) = 0; // slot +0xc: entity type?
        *(undefined4 *)(this[4] + 0x14) = 0; // slot +0x14: data ptr
        *(undefined4 *)(this[4] + 0x18) = 0; // slot +0x18: more data
        return 1;
      }
      index = index + 1;
      slot = slot + 8; // each flag entry is 8 bytes
    } while (index < 0x90);
  }
  return 0;
}