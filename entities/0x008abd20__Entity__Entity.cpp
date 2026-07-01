// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, int isServer)
{
  undefined4 nameId;
  
  if (isServer == 0) {
    nameId = 0;
  }
  else {
    nameId = allocateNameId(); // FUN_00481610
  }
  initializeMemory(1, 1); // FUN_0064d390
  this[0] = &baseVtable; // PTR_LAB_00e317dc
  this[6] = 0; // +0x18: next pointer?
  setNameId(nameId); // FUN_00454a10
  this[9] = 2; // +0x24: type ID
  this[0] = &derivedVtable; // PTR_LAB_00d79f1c
  this[10] = &virtualFunction1; // +0x28: PTR_FUN_00d79ee0
  this[0xc] = &virtualFunction2; // +0x30: LAB_008a89c0
  this[0xd] = 0; // +0x34
  this[0xe] = 0; // +0x38
  this[0xf] = 0; // +0x3c
  this[0x10] = 0; // +0x40
  this[0x11] = 0; // +0x44
  this[0x12] = 0xffffffff; // +0x48: invalid ID
  this[0x13] = 0xffffffff; // +0x4c: invalid ID
  this[0x14] = 0; // +0x50
  this[5] = this + 10; // +0x14: self pointer (offset 40 bytes)
  return this;
}