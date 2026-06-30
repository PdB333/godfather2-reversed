// FUNC_NAME: EARSListContainer::constructor
undefined4 * __thiscall EARSListContainer::constructor(undefined4 *this, byte flags)
{
  undefined4 *currentNode;
  undefined4 *nextNode;
  
  // Set vtable pointers (multiple inheritance?)
  this[6] = &PTR_LAB_00e317cc; // +0x18: secondary vtable
  *this = &PTR_LAB_00e42de4;   // +0x00: primary vtable

  // Clear linked list stored at +0x04
  currentNode = (undefined4 *)this[1];
  while (currentNode != (undefined4 *)0x0) {
    nextNode = (undefined4 *)currentNode[2]; // +0x08: next pointer
    *currentNode = 0;                         // +0x00: zero first field
    currentNode[1] = 0;                       // +0x04: zero second field
    currentNode[2] = 0;                       // +0x08: zero third field (next)
    currentNode = nextNode;
  }

  // Optionally call additional setup if bit 0 of flags is set
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}