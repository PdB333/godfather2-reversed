// FUNC_NAME: Entity::triggerEvent
void __thiscall Entity::triggerEvent(Entity *this, int param2, int param3, int param4, int param5, int param6)
{
  // +0x18: mObjectData (pointer to ObjectData)
  // +0x2c in ObjectData: mEncodedID (uint with tag in top 2 bits)
  uint encodedID = *(uint *)(*(int *)((uint)this + 0x18) + 0x2c);
  uint tag = encodedID & 0xC0000000;
  int resolvedID;

  if (tag == 0) {
    // Tag 0: encodedID is a bit index (bits 5‑9) -> produce bitmask
    resolvedID = 1 << ((encodedID >> 5) & 0x1F);
  }
  else if (tag == 0x40000000) {
    // Tag 1: indexed from global table at offset 8
    resolvedID = *(int *)(encodedID * 4 + 8);
  }
  else if (tag == 0xC0000000) {
    // Tag 2: indexed from global table at offset 0x54
    resolvedID = *(int *)(encodedID * 4 + 0x54);
  }
  else {
    // Tag 3 sentinel (0x80000000) – produce negative error value
    resolvedID = -0x80000000;
  }

  // Dispatch event with type 0x40322 (likely a predefined event ID)
  dispatchEvent(param2, param3, 0x40322, resolvedID, 0, 0, param4, param5, param6);
}