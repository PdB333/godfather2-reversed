// FUNC_NAME: Entity::loadConfiguration
undefined4 * __thiscall Entity::loadConfiguration(undefined4 *this, int dataBlock, undefined4 param3)
{
  undefined4 *pointerEntry;
  uint i;
  
  baseClassInit(dataBlock, param3);  // FUN_00414f30 likely base initializer
  i = 0;
  *this = &vtable_0x00d7c3d0;
  this[0xd] = 0;   // +0x34: some data pointer or ID
  this[0xe] = 0;   // +0x38: another field
  *(undefined1 *)(this + 0xf) = 0;  // +0x3C: byte field (convention: offset in bytes)
  if (*(short *)(dataBlock + 0x20) != 0) {  // count of entries in array
    do {
      pointerEntry = *(undefined4 **)(*(int *)(dataBlock + 0x1c) + i * 4);  // array of pointers
      if (pointerEntry[4] == 0x92CB0516) {  // type hash (e.g., "component" identifier)
        this[0xd] = *pointerEntry;  // store first element of the matching entry
      }
      i = i + 1;
    } while (i < *(ushort *)(dataBlock + 0x20));
  }
  return this;
}